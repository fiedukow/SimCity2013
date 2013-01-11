--Typy dodane do bazy danych
--==========================
BEGIN;

CREATE DOMAIN longitude AS numeric(12,9)
CHECK(
  VALUE between -180.0 and 180.0
);

CREATE DOMAIN latitude AS numeric(11,9)
CHECK(
  VALUE between -90.0 and 90.0
);

CREATE DOMAIN angle AS numeric(6,3)
CHECK(
  VALUE between 0.0 and 360.0
);

CREATE DOMAIN metersOverSee AS numeric(7,2)
CHECK(
  VALUE between -420.0 and 8850
);

COMMENT ON DOMAIN longitude IS 'As degrees (-180 -  180 with 9 positions after coma); +180 = 180E; -180 = 180W;';
COMMENT ON DOMAIN latitude IS 'As degrees (-90 - 90 with 9 positions after coma); +90 = 90N; -90 = 90S;';
COMMENT ON DOMAIN angle IS 'As degrees, rotation of object';
COMMENT ON DOMAIN metersOverSee IS 'As meters over see level (with cm. precision)';


--Baza danych statycznych
--=======================

CREATE TABLE StreetNodes
(
  streetNodeId SERIAL, -- być może będzie można podać id z zewnątrz zapewniając unikalność
                       -- ale auto z bazy musi dbać o to, żeby id automatycznie nie skonfliktowało z tymi wstawionymi ręcznie
  lon longitude not null,
  lat latitude not null,
  mos metersOverSee not null DEFAULT 0,
   
  CONSTRAINT pk_IdOfStreetNode PRIMARY KEY(streetNodeId),
  CONSTRAINT uk_PositionOfNodeUniquness UNIQUE(lon, lat, mos)
);

COMMENT ON TABLE StreetNodes IS 'Contains all vertexes (nodes) of (3D) street graph';
COMMENT ON COLUMN StreetNodes.streetNodeId IS 'Uniqe id of each Node, use for identification in other tables';
COMMENT ON COLUMN StreetNodes.lon IS 'Longitude of vertex (x)';
COMMENT ON COLUMN StreetNodes.lat IS 'Latitude of vertex (x)';
COMMENT ON COLUMN StreetNodes.mos IS 'Meters over see where the vertex is (z)';


CREATE TABLE Streets
(
  streetId SERIAL,
  firstNode integer not null,
  secondNode integer not null,

  CONSTRAINT pk_IdOfStreet PRIMARY KEY(streetId),
  CONSTRAINT fk_firstNode FOREIGN KEY (firstNode) REFERENCES StreetNodes(streetNodeId),
  CONSTRAINT fk_secondNode FOREIGN KEY (secondNode) REFERENCES StreetNodes(streetNodeId),
  CONSTRAINT ck_firstNotEqualSecond CHECK (firstNode <> secondNode)
); 

COMMENT ON TABLE Streets IS 'Constains all edges of (3D) street graph';
COMMENT ON COLUMN Streets.streetId IS 'Uniqe id of each edge used to recognize them';
COMMENT ON COLUMN Streets.firstNode IS 'One of nodes connected with this edge (note:'
                                        'this is undirected graph so order of vertexes does not metter';
COMMENT ON COLUMN Streets.secondNode IS 'One of nodes connected with this edge (note: '
                                        'this is undirected graph so order of vertexes does not metter';
                                                                                                                         
CREATE TABLE Sensors
(
  sensorId SERIAL,
  lon longitude not null,
  lat latitude not null,
  mos metersOverSee not null DEFAULT 0.0,
  range numeric(7,2) not null,
  rotVer angle not null DEFAULT 0.0,
  rotHor angle not null DEFAULT 0.0,
  fov angle not null DEFAULT 180.0,
  
  CONSTRAINT pk_IdOfSensor PRIMARY KEY(sensorId),
  CONSTRAINT ck_range CHECK (range > 0)
);

COMMENT ON TABLE Sensors IS 'Contains staticly placed sensors with informations about their FOV';
COMMENT ON COLUMN Sensors.sensorId IS 'Unique ID of sensor used in dynamic DB';
COMMENT ON COLUMN Sensors.lon IS 'Lontitude of sensor (x position)';
COMMENT ON COLUMN Sensors.lat IS 'Latitude of sensor (y position)';
COMMENT ON COLUMN Sensors.mos IS 'Meters over see of sensor (z position)';
COMMENT ON COLUMN Sensors.range IS 'Range of sensor in meters. How far can sensor see the object';
COMMENT ON COLUMN Sensors.rotVer IS 'Vertical rotation of sensor. 0 is horizontal. 90 is look directly up';
COMMENT ON COLUMN Sensors.rotHor IS 'Horizontal rotation of sensor. 0 is North. 90 is East.';
COMMENT ON COLUMN Sensors.fov IS 'Field of view. Angle in which sensor can see sth.';

CREATE TABLE Prisms
(
  prismId SERIAL,
  mosDown metersOverSee not null DEFAULT 0,
  height numeric(5, 2) not null,
  
  CONSTRAINT pk_IdOfPrism PRIMARY KEY(prismId),
  CONSTRAINT ck_height CHECK (height > 0)
);

COMMENT ON TABLE Prisms IS 'Contains descriptions of Prisms';
COMMENT ON COLUMN Prisms.prismId IS 'Identifier of prism used in other tables';
COMMENT ON COLUMN Prisms.mosDown IS 'Position of bottom wall of the Prism in axis';
COMMENT ON COLUMN Prisms.height IS 'Height of Prism in meters (max. 999.99).';

CREATE TABLE PrismVertexes
(
  prismId integer not null,
  orderPos numeric(5),
  lon longitude not null,
  lat latitude not null,
  
  CONSTRAINT pk_IdPrismVertex PRIMARY KEY(prismId, orderPos),
  CONSTRAINT fk_prismId FOREIGN KEY (prismId) REFERENCES Prisms(prismId)
);

COMMENT ON TABLE PrismVertexes IS 'Contains informations about prisms vertexes';
COMMENT ON COLUMN PrismVertexes.prismId IS 'Id of prism that vertex belongs to';
COMMENT ON COLUMN PrismVertexes.orderPos IS 'Which in order is the vertex for this base polygon';
COMMENT ON COLUMN PrismVertexes.lon IS 'Longitude of this vertex';
COMMENT ON COLUMN PrismVertexes.lat IS 'Latitude of this vertex';



--Baza danych dynamicznych
--========================

CREATE TABLE Observations 
(
  observationId SERIAL,
  cameraTime timestamp not null,
  dbTime timestamp not null DEFAULT current_timestamp,
  lon longitude not null,
  lat latitude not null,
  mos metersOverSee not null DEFAULT 0,
  sensorId integer not null,
  
  CONSTRAINT pk_idOfObservation PRIMARY KEY(observationId),
  CONSTRAINT fk_idOfSensor FOREIGN KEY (sensorId) REFERENCES Sensors(sensorId) 
);


COMMENT ON TABLE Observations IS 'Table containing all samples generated by symulator for tracker analyze';
COMMENT ON COLUMN Observations.observationId IS 'Auto id';
COMMENT ON COLUMN Observations.cameraTime IS 'Synchronized time provided by sensor';
COMMENT ON COLUMN Observations.dbTime IS 'Database time when inserting this row, current_timestamp by default';
COMMENT ON COLUMN Observations.lon IS 'Longitude of place where object was observed';
COMMENT ON COLUMN Observations.lat IS 'Latitude of place where object was observed';
COMMENT ON COLUMN Observations.mos IS 'Meters over see where object was observed';
COMMENT ON COLUMN Observations.sensorId IS 'Reference Id to sensor which made an observation';

END;


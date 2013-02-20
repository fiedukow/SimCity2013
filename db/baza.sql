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

CREATE DOMAIN metersOverSee AS numeric(7,2)
CHECK(
  VALUE between -420.0 and 8850
);

COMMENT ON DOMAIN longitude IS 'As degrees (-180 -  180 with 9 positions after coma); +180 = 180E; -180 = 180W;';
COMMENT ON DOMAIN latitude IS 'As degrees (-90 - 90 with 9 positions after coma); +90 = 90N; -90 = 90S;';
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
                                                                                     
CREATE TABLE SensorTypes
(
  typeId SERIAL,
  typeName varchar(64) not null,

  CONSTRAINT pk_IdOfType PRIMARY KEY(typeId),
  CONSTRAINT uq_UniqueTypeName UNIQUE(typeName)
);

COMMENT ON TABLE SensorTypes IS 'Contains names of sensor types identifying parameters they are providing';
COMMENT ON COLUMN SensorTypes.typeId IS 'Unique ID of type of sensor';
COMMENT ON COLUMN SensorTypes.typeName IS 'Name of type of sensor - human readable';

CREATE TABLE SensorFeatures
(
  featureId SERIAL,
  featureName varchar(64),
  featureType varchar(32),

  CONSTRAINT pk_IdOfFeature PRIMARY KEY(featureId),
  CONSTRAINT uq_uniqueFeatureName UNIQUE(featureName)
);

COMMENT ON TABLE SensorFeatures IS 'Description of features of Sensor. Each row describe one type of information that can be provided by sensor';
COMMENT ON COLUMN SensorFeatures.featureId IS 'Unique ID of sensor feature';
COMMENT ON COLUMN SensorFeatures.featureName IS 'The name of feature which identify it from any other feature';
COMMENT ON COLUMN SensorFeatures.featureType IS 'Identifier of type understandable for application using this db, eg. "STRING", "INT" etc.'; 
 
CREATE TABLE SensorTypesFeatures
(
  typeId integer not null,
  featureId integer not null,

  CONSTRAINT pk_SensorTypesFeatures PRIMARY KEY(typeId, featureId),
  CONSTRAINT fk_IdOfSensorType FOREIGN KEY(typeId) REFERENCES SensorTypes(typeId),
  CONSTRAINT fk_IdOfFeature FOREIGN KEY(featureId) REFERENCES SensorFeatures(featureId)
);

COMMENT ON TABLE SensorTypesFeatures IS 'Describes connection between types of sensors and features they are providing';
COMMENT ON COLUMN SensorTypesFeatures.typeId IS 'Id of sensor type connected with feature';
COMMENT ON COLUMN SensorTypesFeatures.featureId IS 'Id of feature connected with sensor type';

CREATE TABLE Sensors
(
  sensorId SERIAL,
  typeId integer not null,
  lon longitude not null,
  lat latitude not null,
  mos metersOverSee not null DEFAULT 0.0,
  range numeric(7,2) not null,
  
  CONSTRAINT pk_IdOfSensor PRIMARY KEY(sensorId),
  CONSTRAINT fk_sensorType FOREIGN KEY(typeId) REFERENCES SensorTypes(typeId)
);

COMMENT ON TABLE Sensors IS 'Contains staticly placed sensors';
COMMENT ON COLUMN Sensors.sensorId IS 'Unique ID of sensor used in dynamic DB';
COMMENT ON COLUMN Sensors.lon IS 'Lontitude of sensor (x position)';
COMMENT ON COLUMN Sensors.lat IS 'Latitude of sensor (y position)';
COMMENT ON COLUMN Sensors.mos IS 'Meters over see of sensor (z position)';
COMMENT ON COLUMN Sensors.range IS 'Range of ';
COMMENT ON COLUMN Sensors.typeId IS 'Id of type of sensor known for applications working with DB';

CREATE TABLE SensorsDetails
(
  sensorId integer not null,
  key varchar(255) not null,
  value varchar(255) not null,
  CONSTRAINT pk_IdOfSensorDetail PRIMARY KEY(sensorId, key),
  CONSTRAINT fk_sensorId FOREIGN KEY (sensorId) REFERENCES Sensors(sensorId)
);

comment ON TABLE SensorsDetails IS 'Contains parameters of sensors in db as (key -> value)';
comment ON COLUMN SensorsDetails.sensorId IS 'Id of sensor which details is row describing';
comment ON COLUMN SensorsDetails.key IS 'Name of parameter in the row';
comment ON COLUMN SensorsDetails.value IS 'Value of parameter';

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

END;


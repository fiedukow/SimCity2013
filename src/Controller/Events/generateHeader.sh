#!/bin/sh
nazwa=$1;
nazwaUp=`echo $nazwa | tr '[:lower:]' '[:upper:]'`

echo "#ifndef $nazwaUp""_H"
echo "#define $nazwaUp""_H";
echo "#include <Controller/Events/EventBase.h>"
echo
echo "namespace SimCity"
echo "{"
echo "namespace Controller"
echo "{"
echo "namespace Events"
echo "{"
echo 
echo "class $nazwa : public EventBase"
echo "{"
echo "public:";
echo "  void accept(Controller& visitor);"
echo "};"
echo 
echo "}//namespace Events"
echo "}//namespace Controller"
echo "}//namespace SimCity"
echo
echo "#endif // EVENTBASE_H"



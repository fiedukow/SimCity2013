#!/bin/sh
nazwa=$1;
nazwaUp=`echo $nazwa | tr '[:lower:]' '[:upper:]'`

echo "#include \"$nazwa.h\""
echo "#include <Controller/Controller.h>"
echo
echo "namespace SimCity"
echo "{"
echo "namespace Controller"
echo "{"
echo "namespace Events"
echo "{"
echo 
echo "void $nazwa::accept(Controller& visitor)"
echo "{"
echo "  visitor.visit(*this);"; 
echo "}"
echo 
echo "}//namespace Events"
echo "}//namespace Controller"
echo "}//namespace SimCity"
echo


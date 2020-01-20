#!/usr/bin/env sh

testing_todo()
{

FILE="result_$1"
echo "$FILE"
if [ -e $FILE ]
then
  rm $FILE
fi
while IFS="" read -r p || [ -n "$p" ]
do
  sh testing.sh $p >> $FILE
done < $1
}

testing_todo $1
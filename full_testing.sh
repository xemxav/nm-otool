#!/usr/bin/env sh

NM="nm"
NM_PERSO="./ft_nm"

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

test_nm()
{
  (eval ${NM_PERSO} $1) > my_result.txt
  (eval ${NM} $1) > off_result.txt
  diff my_result.txt off_result.txt > diff.txt
  if [ $? != 0 ]
  then
      echo $1
  fi
  rm diff.txt
  rm my_result.txt
  rm off_result.txt
}


full_testing()
{
  for filename in $1/*; do
    test_nm $filename
  done
}

full_testing $1 > to_do_list.txt
cat to_do_list.txt
testing_todo to_do_list.txt
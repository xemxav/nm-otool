#!/usr/bin/env sh

NM="nm"
NM_PERSO="./ft_nm"

test_nm()
{
  echo $1
  (eval ${NM_PERSO} $1) > my_result
  (eval ${NM} $1) > off_result
  diff my_result off_result
    if [ $? -eq 0 ]
    then
      echo ' ok'
      rm my_result
      rm off_result
    else
      echo $?
    fi

}

test_nm $1
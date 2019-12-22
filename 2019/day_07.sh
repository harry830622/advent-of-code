#!/bin/env bash

phase_1=-1
phase_2=-1
phase_3=-1
phase_4=-1
phase_5=-1

is_shown=(0 0 0 0 0)

max_out=0

for phase_1 in 0 1 2 3 4; do
  is_shown[$phase_1]=1
  for phase_2 in 0 1 2 3 4; do
    if [ "${is_shown["$phase_2"]}" -eq "1" ]; then
      continue
    fi
    is_shown[$phase_2]=1
    for phase_3 in 0 1 2 3 4; do
      if [ "${is_shown["$phase_3"]}" -eq "1" ]; then
        continue
      fi
      is_shown[$phase_3]=1
      for phase_4 in 0 1 2 3 4; do
        if [ "${is_shown["$phase_4"]}" -eq "1" ]; then
          continue
        fi
        is_shown[$phase_4]=1
        for phase_5 in 0 1 2 3 4; do
          if [ "${is_shown["$phase_5"]}" -eq "1" ]; then
            continue
          fi
          echo "$phase_1 $phase_2 $phase_3 $phase_4 $phase_5"
          amp_1=$(cat ./day_07.in <(echo $phase_1) <(echo 0) | ./day_05)
          amp_2=$(cat ./day_07.in <(echo $phase_2) <(echo $amp_1) | ./day_05)
          amp_3=$(cat ./day_07.in <(echo $phase_3) <(echo $amp_2) | ./day_05)
          amp_4=$(cat ./day_07.in <(echo $phase_4) <(echo $amp_3) | ./day_05)
          amp_5=$(cat ./day_07.in <(echo $phase_5) <(echo $amp_4) | ./day_05)
          if [ "$amp_5" -gt "$max_out" ]; then
            max_out=$amp_5
          fi
          is_shown[$phase_5]=0
        done
        is_shown[$phase_4]=0
      done
      is_shown[$phase_3]=0
    done
    is_shown[$phase_2]=0
  done
  is_shown[$phase_1]=0
done

echo $max_out

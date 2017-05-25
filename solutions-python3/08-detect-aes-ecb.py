#!/usr/bin/env python3

def repetition_score(line):
  length = len(line)
  score =0
  for i in range(0, length, 32):
    for j in range(i + 32, length, 32):
      if line[i:i + 32] == line[j:j+32]:
        score +=1
  return score

file = open("8.txt")

max_score = 0
possible_line = b''
for line in file:
  score = repetition_score(line.rstrip())
  if score > max_score:
    possible_line = line
    max_score = score

print(possible_line)

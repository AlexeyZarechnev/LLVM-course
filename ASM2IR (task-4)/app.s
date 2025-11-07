ENTRYPOINT:
  add x1 sp 0
  add sp sp 606416
  add x2 sp 0
  add sp sp 606416
  FILL_INIT_STATE x1
  add x3 1 0
  add x4 1 0

FIRST_CYCLE_COUNT:
  add x6 0 0
  gep2 x5 502 x1 x3 x4 0 1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x1 x3 x4 0 -1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x1 x3 x4 1 0
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x1 x3 x4 -1 0
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x1 x3 x4 -1 -1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x1 x3 x4 -1 1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x1 x3 x4 1 -1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x1 x3 x4 1 1
  load x5 x5
  add x6 x6 x5
  eq x7 x6 3
  br_cond x7 FIRST_CYCLE_CONDITION
  gep2 x5 502 x2 x3 x4 0 0
  store x5 1
  add x5 16777215 0
  br FIRST_CYCLE_END

FIRST_CYCLE_CONDITION:
  gep2 x5 502 x1 x3 x4 0 0
  load x5 x5
  eq x5 x5 1
  eq x6 x6 2
  add x6 x5 x6
  eq x6 x6 2
  gep2 x5 502 x2 x3 x4 0 0
  store x5 x6
  mul x5 x6 16777215

FIRST_CYCLE_END:
  sub x6 x3 1
  sub x7 300 x4
  PUT_PIXEL x6 x7 x5
  add x4 x4 1
  neq x5 x4 301
  br_cond x5 FIRST_CYCLE_COUNT
  add x3 x3 1
  neq x5 x3 501
  br_cond x5 FIRST_CYCLE_COUNT
  FLUSH x5
  neq x5 x5 0
  add x3 1 0
  add x4 1 0
  br_cond x5 EXITPOINT

SECOND_CYCLE_COUNT:
  add x6 0 0
  gep2 x5 502 x2 x3 x4 0 1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x2 x3 x4 0 -1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x2 x3 x4 1 0
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x2 x3 x4 -1 0
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x2 x3 x4 -1 -1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x2 x3 x4 -1 1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x2 x3 x4 1 -1
  load x5 x5
  add x6 x6 x5
  gep2 x5 502 x2 x3 x4 1 1
  load x5 x5
  add x6 x6 x5
  eq x7 x6 3
  br_cond x7 SECOND_CYCLE_CONDITION
  gep2 x5 502 x1 x3 x4 0 0
  store x5 1
  add x5 16777215 0
  br SECOND_CYCLE_END

SECOND_CYCLE_CONDITION:
  gep2 x5 502 x2 x3 x4 0 0
  load x5 x5
  eq x5 x5 1
  eq x6 x6 2
  add x6 x5 x6
  eq x6 x6 2
  gep2 x5 502 x1 x3 x4 0 0
  store x5 x6
  mul x5 x6 16777215

SECOND_CYCLE_END:
  sub x6 x3 1
  sub x7 300 x4
  PUT_PIXEL x6 x7 x5
  add x4 x4 1
  neq x5 x4 301
  br_cond x5 SECOND_CYCLE_COUNT
  add x3 x3 1
  neq x5 x3 501
  br_cond x5 SECOND_CYCLE_COUNT
  FLUSH x5
  neq x5 x5 1
  add x3 1 0
  add x4 1 0
  br_cond x5 FIRST_CYCLE_COUNT

EXITPOINT:
  EXIT

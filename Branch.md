# Before

 | data | cycles | time(ms) | success rate |
 |---|---|---|---|
 | ../data/naive.data | 34 | 4.922ms | nan% | 
 | ../tests/data-hazard-1.hex | 11 | 0.479ms | nan% | 
 | ../tests/data-hazard-2.hex | 12 | 0.464ms | nan% | 
 | ../tests/control-hazard-1.hex | 11 | 0.446ms | nan% | 
 | ../tests/control-hazard-2.hex | 13 | 0.449ms | 0% | 
 | ../data/array_test1.data | 218 | 0.546ms | 54.5455% | 
 | ../data/array_test2.data | 247 | 0.544ms | 50% | 
 | ../data/basicopt1.data | 633149 | 56.926ms | 58.9774% | 
 | ../data/bulgarian.data | 419969 | 40.403ms | 50.6399% | 
 | ../data/expr.data | 632 | 0.936ms | 37.8378% | 
 | ../data/gcd.data | 546 | 0.641ms | 62.5% | 
 | ../data/hanoi.data | 201773 | 19.043ms | 49.98% | 
 | ../data/lvalue2.data | 61 | 1.49ms | 66.6667% | 
 | ../data/magic.data | 582014 | 45.829ms | 53.1436% | 
 | ../data/manyarguments.data | 71 | 0.646ms | 80% | 
 | ../data/multiarray.data | 1777 | 0.963ms | 18.5185% | 
 | ../data/qsort.data | 1590883 | 107.458ms | 30.0067% | 
 | ../data/queens.data | 607530 | 38.524ms | 63.2216% | 
 | ../data/statement_test.data | 1115 | 0.56ms | 59.4059% | 
 | ../data/superloop.data | 577259 | 34.466ms | 87.2946% | 
 | ../data/tak.data | 1546200 | 90.022ms | 74.9996% | 
 | ../data/pi.data | 127443492 | 8041.23ms | 42.2702% | 

# After

 | data | cycles | time(ms) | success rate |
 |---|---|---|---|
 | ../data/naive.data | 33 | 5.337ms | nan% | 
 | ../tests/data-hazard-1.hex | 11 | 0.729ms | nan% | 
 | ../tests/data-hazard-2.hex | 12 | 0.571ms | nan% | 
 | ../tests/control-hazard-1.hex | 10 | 0.582ms | nan% | 
 | ../tests/control-hazard-2.hex | 13 | 0.582ms | 0% | 
 | ../data/array_test1.data | 209 | 0.655ms | 54.5455% | 
 | ../data/array_test2.data | 237 | 1.047ms | 50% | 
 | ../data/basicopt1.data | 559226 | 52.074ms | 98.8887% | 
 | ../data/bulgarian.data | 377506 | 35.758ms | 94.4862% | 
 | ../data/expr.data | 586 | 3.846ms | 75.6757% | 
 | ../data/gcd.data | 534 | 3.514ms | 61.6667% | 
 | ../data/hanoi.data | 190794 | 18.921ms | 86.4868% | 
 | ../data/lvalue2.data | 59 | 0.95ms | 66.6667% | 
 | ../data/magic.data | 553419 | 46.586ms | 82.2054% | 
 | ../data/manyarguments.data | 69 | 0.912ms | 80% | 
 | ../data/multiarray.data | 1650 | 1.03ms | 66.0494% | 
 | ../data/qsort.data | 1430582 | 98.468ms | 91.7384% | 
 | ../data/queens.data | 582242 | 41.592ms | 81.0156% | 
 | ../data/statement_test.data | 1067 | 2.527ms | 66.8317% | 
 | ../data/superloop.data | 532844 | 42.246ms | 95.1932% | 
 | ../data/tak.data | 1530613 | 101.747ms | 75.7038% | 
 | ../data/pi.data | 109722503 | 8114.27ms | 84.5072% | 

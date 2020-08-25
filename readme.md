# weights
Converts weights between kilograms and pounds.

## usage
```
weights -w <vlaue> -f <unit> -t <unit>
```

where `<unit>` is one of the following:
- `k`: kilograms
- `l`: pounds
- `s`: stone and pounds

## examples
```
$ ./out/weights -f k -t l -w 100
100 kg is approximately equal to 220.462 lb

$ ./out/weights -f k -t s -w 100
100 kg is approximately equal to 15 st 10.4623 lb

$ ./out/weights -f s -t k -w "15 10"
15 st 10 lb is approximately equal to 99.7903 kg
```

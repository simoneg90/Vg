# Vg

## Instructions for CMSSW_7_1_5

Default fit files are looked for in 

```
../fitFilesBtagSF/btag/
../fitFilesBtagSF/antibtag/
histos_bkg.root
histos_signal-750.root
histos_signal-1.root
histos_signal-2.root
histos_signal-3.root
```

To run background fit:

```
.x BackgroundPrediction.c("antibtag",20)
```

To run signal fit:

```
.x Display_SignalFits.cc("antibtag","../fitFilesBtagSF/","","histos_signal-",1000,10)
```

To create workspace:

```
./buildInputs.sh 10 750
```

To build datacards:

```
./buildDatacards.sh 750
```

To run limits:

```
./runLimits.sh 0 750
```

To run everything:

```
./doLimits.sh
```

combine datacard_qqg_750_combined_alt.txt -M GenerateOnly -m 750 -t 300  --saveToys -s 334455 --expectSignal=0.136 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_lau1 -n biasTest

combine datacard_qqg_750_combined.txt -M MaxLikelihoodFit -m 750 --expectSignal=0.136 --noErrors --minos none --rMin=-40 --rMax=40 -t 300 --toysFile=higgsCombinebiasTest.GenerateOnly.mH750.334455.root -s 334455 -n output750

combine datacard_qqg_750_combined_alt.txt -M GenerateOnly -m 750 -t 300  --saveToys -s 334455 --expectSignal=0.680 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_lau1 -n biasTest_5

combine datacard_qqg_750_combined.txt -M MaxLikelihoodFit -m 750 --expectSignal=0.680 --noErrors --minos none --rMin=-4 --rMax=4 -t 300 --toysFile=higgsCombinebiasTest_5.GenerateOnly.mH750.334455.root -s 334455 -n output750_5

combine datacard_qqg_750_combined_alt.txt -M GenerateOnly -m 750 -t 300  --saveToys -s 334455 --expectSignal=0.408 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_lau1 -n biasTest_3

combine datacard_qqg_750_combined.txt -M MaxLikelihoodFit -m 750 --expectSignal=0.408 --noErrors --minos none --rMin=-40 --rMax=40 -t 300 --toysFile=higgsCombinebiasTest_3.GenerateOnly.mH750.334455.root -s 334455 -n output750_3


combine datacard_qqg_2000_combined_alt.txt -M GenerateOnly -m 2000 -t 300  --saveToys -s 334455 --expectSignal=0.016 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_lau1 -n biasTest2000

combine datacard_qqg_2000_combined.txt -M MaxLikelihoodFit -m 2000 --expectSignal=0.016 --noErrors --minos none --rMin=-4 --rMax=4 -t 300 --toysFile=higgsCombinebiasTest2000.GenerateOnly.mH2000.334455.root -s 334455 -n output2000

combine datacard_qqg_2000_combined_alt.txt -M GenerateOnly -m 2000 -t 300  --saveToys -s 334455 --expectSignal=0.080 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_lau1 -n biasTest2000_5

combine datacard_qqg_2000_combined.txt -M MaxLikelihoodFit -m 2000 --expectSignal=0.08 --noErrors --minos none --rMin=-30 --rMax=30 -t 200 --toysFile=higgsCombinebiasTest2000_5.GenerateOnly.mH2000.334455.root -s 334455 -n output2000_5



combine datacard_qqg_2000_combined_alt.txt -M GenerateOnly -m 2000 -t 300  --saveToys -s 334455 --expectSignal=0.048 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_lau1 -n biasTest2000_3

combine datacard_qqg_2000_combined.txt -M MaxLikelihoodFit -m 2000 --expectSignal=0.048 --noErrors --minos none --rMin=-4 --rMax=4 -t 300 --toysFile=higgsCombinebiasTest2000_3.GenerateOnly.mH2000.334455.root -s 334455 -n output2000_3

#!/bin/sh

./build.sh

echo "Test case 1: Defector vs suspicious doormat"
./bin/prisoners_dilemma config/test_defector_vs_susp_doormat_config.json
echo "Expected result:"
echo "Defector: 996"
echo "Suspicious doormat: 1"
echo "Actual result:"
tail -n 2 out/test_defector_vs_susp_doormat_log.csv
echo ""

echo "Test case 2: Suspicious TFT vs suspicious cooperator"
./bin/prisoners_dilemma config/test_susp_tft_vs_susp_cooperator_config.json
echo "Expected result:"
echo "Suspicious TFT: 600"
echo "Suspicious cooperator: 595"
echo "Actual result:"
tail -n 2 out/test_susp_tft_vs_susp_cooperator_log.csv
echo ""

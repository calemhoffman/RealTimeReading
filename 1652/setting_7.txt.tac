//============= Discriminator
700     //Tigger Threshold (in LSB)
496     // Trigger Hold Off
64      // Fast Discriminator smooth, Trigger Filter smoothing factor (number of samples to average for RC-CR2 filter) Options: 1; 2; 4; 8; 16; 32
100     // Input Signal Rise time (ns) 
//============= Trapezoid
496    // Trapezoid Rise Time (ns) 
1.000    // Trapezoid Flat Top  (ns) 
496   // Decay Time Constant (ns) 
1000     // Flat top delay (peaking time) (ns) 
2       // Ns peak, Peak mean (number of samples to average for trapezoid height calculation). Options: 0-> 1 sample; 1->4 samples; 2->16 samples; 3->64 samples
960     // Peak holdoff (ns)
//============= Input
3       // Ns baseline, number of samples for baseline average calculation. Options: 1->16 samples; 2->64 samples; 3->256 samples; 4->1024 samples; 5->4096 samples; 6->16384 samples
0       // input dynamic range, 0 = 2 Vpp, 1 = 0.5 Vpp
//============= Others
0.8     // DC offset ( from 0 to 1 )
2000    // pre trigger size [ch];
true    // is pulse positive parity;
1       // Energy fine gain , may be address is incorrect? seem no effect
500     // Baseline holdoff (ns)
1.00     // Energy Normalization Factor 
0       // decimation (the input signal samples are averaged within this number of samples): 0 ->disabled; 1->2 samples; 2->4 samples; 3->8 samples
0       // decimation gain. Options: 0->DigitalGain=1; 1->DigitalGain=2 (only with decimation >= 2samples); 2->DigitalGain=4 (only with decimation >= 4samples); 3->DigitalGain=8( only with decimation = 8samples).
0       // Enable Rise time Discrimination. Options: 0->disabled; 1->enabled
100     // Rise Time Validation Window (ns)
//============= software channel gain
1.0      // if 1.0, use dynamic range, if any channel is not 1, will use gain for its own channel
0        // range min [ch]
5000     // range max [ch]

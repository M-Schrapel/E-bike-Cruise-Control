# Dataset

The anonymized dataset is provided as it is for research purposes. It contains data from 15 cyclists in randomized order. The data were collected within a study with 15 participants cycling on a straight road with a length of 300m. In the following, we provide a short explanation of the files.

***meas_speed_raw_limit.csv*** contains raw measured speeds of cyclists in relation to the cycled speed and motor mode. In mode None, the cyclists were not supported by the engine. The dataset contains 3 columns: 

	- MeasuredSpeed: The measured speed.
	- Mode: Motor modes None (no electrical support), "E" = Eco (minimal support), "T" = Turbo (maximal support)
	- SpeedLimit: At which CC speed limit the report was taken

***meas_speed_norm_mode.csv*** contains processed measured speeds of cyclists normalized by the speed limit (in Eco and Turbo mode) and preferred cycled speed (in None mode). The dataset contains 2 columns:

	- Mode: Motor modes None (no electrical support), "E" = Eco (minimal support), "T" = Turbo (maximal support)
	- NormedSpeed: Normalized measured speed in relation to the cycled speed

***report_speed_raw_limit.csv*** contains plain perceived speeds of cyclists in relation to the cycled speed and motor mode. In mode None, the cyclists were not supported by the engine. The dataset contains 3 columns: 

	- MeasuredSpeed: The reported speed.
	- Mode: Motor modes None (no electrical support), Eco (minimal support), Turbo (maximal support)
	- SpeedLimit: At which CC speed limit the report was taken

***meas_speed_norm_mode.csv*** contains processed reported speeds of cyclists normalized by the speed limit (in Eco and Turbo mode) and 0km/h (in None mode). The dataset contains 2 columns:

	- Mode: Motor modes None (no electrical support), "E" = Eco (minimal support), "T" = Turbo (maximal support)
	- NormedSpeed: Normalized reported speed in relation to the cycled speed

***tlx_raw_norm_mode.csv*** contains NASA-TLX Score measurements in relation to the motor modes Eco, Turbo and None. The TLX questions were assessed after cycling 300m with CC. The dataset contains 2 columns:

	- Mode: Motor modes None (no electrical support), "E" = Eco (minimal support), "T" = Turbo (maximal support)
	- TLX Score: Calculated TLX score

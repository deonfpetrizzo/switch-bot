class PhotoResistor {
	private:
		int ldrPin;
		int vin;
		int r;

	public:
		PhotoResistor(int ldrPin, int vin, int r, int maxLumen, int minLumen) {
			this->ldrPin = ldrPin;
			this->vin = vin;
			this->r = r;
		}

		void init() {
			pinMode(ldrPin, INPUT);
		}

		int read() {
			return adcToLumen(analogRead(ldrPin));
		}

	private:	
		int adcToLumen(int adc) {
		  	float vOut = float(adc) * (vin/float(1023));
		  	float rLDR = (r * (vin - vOut))/vOut; 
		  	int phys = 500/(rLDR/1000);
		  	return phys;
		}
};
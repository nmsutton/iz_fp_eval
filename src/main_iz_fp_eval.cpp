/* * Copyright (c) 2016 Regents of the University of California. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* 3. The names of its contributors may not be used to endorse or promote
*    products derived from this software without specific prior written
*    permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* *********************************************************************************************** *
* CARLsim
* created by: (MDR) Micah Richert, (JN) Jayram M. Nageswaran
* maintained by:
* (MA) Mike Avery <averym@uci.edu>
* (MB) Michael Beyeler <mbeyeler@uci.edu>,
* (KDC) Kristofor Carlson <kdcarlso@uci.edu>
* (TSC) Ting-Shuo Chou <tingshuc@uci.edu>
* (HK) Hirak J Kashyap <kashyaph@uci.edu>
*
* CARLsim v1.0: JM, MDR
* CARLsim v2.0/v2.1/v2.2: JM, MDR, MA, MB, KDC
* CARLsim3: MB, KDC, TSC
* CARLsim4: TSC, HK
* CARLsim5: HK, JX, KC
* CARLsim6: LN, JX, KC, KW
*
* CARLsim available from http://socsci.uci.edu/~jkrichma/CARLsim/
* Ver 12/31/2016
*/

#include <carlsim.h> // include CARLsim user interface

int main() {
	// ---------------- CONFIG STATE -------------------	
	int randSeed = 42; int numGPUs = 1;
	CARLsim sim("hello world", GPU_MODE, USER, numGPUs, randSeed);
	int dummy = sim.createSpikeGeneratorGroup("dummy_connection", 1, EXCITATORY_NEURON, 0, GPU_CORES);
	int MEC_LII_Stellate=sim.createGroup("MEC_LII_Stellate", 1, EXCITATORY_NEURON, ANY, GPU_CORES);
	sim.setNeuronParameters(MEC_LII_Stellate, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 
	0.0f, -43.52f, 0.0f, 0.005f, 0.0f, 11.690000f, 0.0f, 11.48f, 0.0f, -49.52f, 0.0f, 
    3.0f, 0.0f, 1);
	sim.connect(dummy, MEC_LII_Stellate, "one-to-one", 0.0f, SYN_FIXED); // CARLsim seems to require at least one connection
	sim.setNeuronMonitor(MEC_LII_Stellate,"DEFAULT");	
	// ---------------- SETUP STATE -------------------
	sim.setupNetwork();
	SpikeMonitor* SMexc = sim.setSpikeMonitor(MEC_LII_Stellate, "DEFAULT");
	// ---------------- RUN STATE -------------------
	SMexc->startRecording();
	for (int i=0; i<100; i++) {
		if (i==4) {
			sim.setExternalCurrent(MEC_LII_Stellate, 300.0f);
		}
		if (i==14) {
			sim.setExternalCurrent(MEC_LII_Stellate, 0.0f);
		}
		sim.runNetwork(0,100, false);
	}
	SMexc->stopRecording(); printf("\n\n");
	SMexc->print(false); // print firing stats	
	
	return 0;
}
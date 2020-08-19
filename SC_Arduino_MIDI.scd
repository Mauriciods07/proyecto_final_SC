(
// Paso 1
// Poner el cursor en esta línea y presionar
// control enter en GNU/Linux y Windows
// comand enter en mac
s.boot;
MIDIIn.connect;
)

(
SynthDef( \misynth, {arg freq=200,amp = 0.5,pan =0;
	var osc, env, output;
	osc = amp*SinOsc.ar(freq);
	output = osc ;
	Out.ar(0,Pan2.ar(output, pan=0)
	)
}).add;
)

(
// Paso 2
// Poner el cursor en esta línea y presionar
// control enter en GNU/Linux y Windows
// comand enter en mac

a=Synth(\misynth);
~noteOn = { arg src, chan, num, vel;
	 [chan,num,vel / 127].postln;
	// 3
	a.set(\freq,num.midicps);
	a.set(\amp,vel);

};
MIDIIn.addFuncTo(\noteOn, ~noteOn);
)


//cleanup
(
MIDIIn.removeFuncFrom(\noteOn, ~noteOn);
MIDIIn.removeFuncFrom(\noteOff, ~noteOff);
MIDIIn.removeFuncFrom(\polytouch, ~polytouch);
MIDIIn.removeFuncFrom(\control, ~control);
MIDIIn.removeFuncFrom(\program, ~program);
MIDIIn.removeFuncFrom(\touch, ~touch);
MIDIIn.removeFuncFrom(\bend, ~bend);
MIDIIn.removeFuncFrom(\sysex, ~sysex);
MIDIIn.removeFuncFrom(\sysrt, ~sysrt);
MIDIIn.removeFuncFrom(\smpte, ~smpte);
)

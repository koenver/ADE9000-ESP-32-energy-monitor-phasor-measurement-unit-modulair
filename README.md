<html>

<head>
<meta http-equiv=Content-Type content="text/html; charset=windows-1252">
<meta name=Generator content="Microsoft Word 15 (filtered)">
<style>
<!--
 /* Font Definitions */
 @font-face
	{font-family:Wingdings;
	panose-1:5 0 0 0 0 0 0 0 0 0;}
@font-face
	{font-family:"Cambria Math";
	panose-1:2 4 5 3 5 4 6 3 2 4;}
@font-face
	{font-family:Calibri;
	panose-1:2 15 5 2 2 2 4 3 2 4;}
 /* Style Definitions */
 p.MsoNormal, li.MsoNormal, div.MsoNormal
	{margin-top:0cm;
	margin-right:0cm;
	margin-bottom:8.0pt;
	margin-left:0cm;
	line-height:107%;
	font-size:11.0pt;
	font-family:"Calibri",sans-serif;}
p.MsoListParagraph, li.MsoListParagraph, div.MsoListParagraph
	{margin-top:0cm;
	margin-right:0cm;
	margin-bottom:8.0pt;
	margin-left:36.0pt;
	line-height:107%;
	font-size:11.0pt;
	font-family:"Calibri",sans-serif;}
p.MsoListParagraphCxSpFirst, li.MsoListParagraphCxSpFirst, div.MsoListParagraphCxSpFirst
	{margin-top:0cm;
	margin-right:0cm;
	margin-bottom:0cm;
	margin-left:36.0pt;
	margin-bottom:.0001pt;
	line-height:107%;
	font-size:11.0pt;
	font-family:"Calibri",sans-serif;}
p.MsoListParagraphCxSpMiddle, li.MsoListParagraphCxSpMiddle, div.MsoListParagraphCxSpMiddle
	{margin-top:0cm;
	margin-right:0cm;
	margin-bottom:0cm;
	margin-left:36.0pt;
	margin-bottom:.0001pt;
	line-height:107%;
	font-size:11.0pt;
	font-family:"Calibri",sans-serif;}
p.MsoListParagraphCxSpLast, li.MsoListParagraphCxSpLast, div.MsoListParagraphCxSpLast
	{margin-top:0cm;
	margin-right:0cm;
	margin-bottom:8.0pt;
	margin-left:36.0pt;
	line-height:107%;
	font-size:11.0pt;
	font-family:"Calibri",sans-serif;}
.MsoChpDefault
	{font-family:"Calibri",sans-serif;}
.MsoPapDefault
	{margin-bottom:8.0pt;
	line-height:107%;}
@page WordSection1
	{size:595.3pt 841.9pt;
	margin:70.85pt 70.85pt 70.85pt 70.85pt;}
div.WordSection1
	{page:WordSection1;}
 /* List Definitions */
 ol
	{margin-bottom:0cm;}
ul
	{margin-bottom:0cm;}
-->
</style>

</head>

<body lang=NL>

<div class=WordSection1>

<p class=MsoNormal><b><span style='font-size:14.0pt;line-height:107%;
font-family:"Arial",sans-serif'>ADE9000-ESP-32-energy-monitor-phasor-measurement-unit-modulair</span></b></p>

<p class=MsoNormal><i><span style='font-family:"Arial",sans-serif'>Prototype
version of an Energy Measurement / Phasor Measurement unit with modulair
interface modules  </span></i></p>

<p class=MsoNormal><b><span style='font-family:"Arial",sans-serif'>Specs:</span></b></p>

<p class=MsoListParagraphCxSpFirst style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>ESP-32 processor
(with double SPI and multicore multi tasking) and Wifi </span></p>

<p class=MsoListParagraphCxSpMiddle style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>galvanic seperation
with ADUM chips </span></p>

<p class=MsoListParagraphCxSpMiddle style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>ADE9000 3 phase
Energy Measurement IC , version for CT (5VA) or </span></p>

<p class=MsoListParagraphCxSpMiddle><span style='font-family:"Arial",sans-serif'>rogowski
(0.1mV/A), 8kHz wavebuffering , harmonics analyses and </span></p>

<p class=MsoListParagraphCxSpMiddle><span style='font-family:"Arial",sans-serif'>event
processing for 50Hz , 230V 3 phase Energy systems </span></p>

<p class=MsoListParagraphCxSpMiddle style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>module 1 slot: 485
interface / lorawan 868 Mhz/ Ethernet lan8720 (wave share)</span></p>

<p class=MsoListParagraphCxSpMiddle><span style='font-family:"Arial",sans-serif'>                        
/ NB-Iot-LTE-M (Ublox) </span></p>

<p class=MsoListParagraphCxSpMiddle style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>modele 2 slot: Ublox
GPS / DS3232 RTC </span></p>

<p class=MsoListParagraphCxSpMiddle style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>uppper expansion
board: 485 interface, 2x 24lc512, mcp23017, ds2482, mcp4725,BME680; </span></p>

<p class=MsoListParagraphCxSpMiddle><span style='font-family:"Arial",sans-serif'>so
4 DI (opto), 4 DO (opto), 1-wire , temp, humidity, voc, air ppressure, AD en DA
and extra flash </span></p>

<p class=MsoListParagraphCxSpMiddle style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>optional I2C
display  (SED1306 or H35B-I)</span></p>

<p class=MsoListParagraphCxSpLast style='text-indent:-18.0pt'><span
style='font-family:Symbol'>·<span style='font:7.0pt "Times New Roman"'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span></span><span style='font-family:"Arial",sans-serif'>Arduino IDE , in
RTOS , C++ Language </span></p>

<p class=MsoNormal><span style='font-family:"Arial",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal><span style='font-family:"Arial",sans-serif'>Now in testing
phase -&gt; so only use parts which I confirmed status <b><i>tested</i></b> </span></p>

<p class=MsoNormal><span style='font-family:"Arial",sans-serif'>&nbsp;</span></p>

<p class=MsoNormal><i><span style='font-family:"Arial",sans-serif'>Software
will be open source and soft- and hardware which are based on this </span></i></p>

<p class=MsoNormal><i><span style='font-family:"Arial",sans-serif'>project by
others have the obligation of open source and publishing at Github</span></i></p>

</div>

</body>

</html>

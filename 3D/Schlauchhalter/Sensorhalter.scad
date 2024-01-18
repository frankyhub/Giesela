/*
*******************************************
Objekt Info: Sensorhalter
                Ecken abrunden mit cuboid
                polygon

*******************************************
Version: 14.03.2023 khf
//***************   Auswahl   *************
keine
//*****************************************

//***************   Libraries  ************/
include <lib/std.scad>
//*****************************************/

//***************  Parameter   *************
//keine
//**************   Programm  **************/

//Dreieck
translate(v = [34, 0, -2]) { 
    linear_extrude(height = 4)
polygon(
 points=[
 [0,0],    // Punkt 0
 [0,6.5],  // Punkt 1
 [30,0], // Punkt 2
 [0,-6.5]   // Punkt 3
    
],
 paths=[
 [0,1,2,3] // 4 Verbindungen
]
);
}



//Grundkoerper
difference() {
cuboid(
    [70,10,4], rounding=1,
    edges=[
    TOP+FRONT,
    TOP+BACK,
    TOP+LEFT,
//    TOP+RIGHT,
    
    DOWN+FRONT,
    DOWN+BACK,
    DOWN+LEFT,
//    DOWN+RIGHT,
    
    FRONT+RIGHT,
    FRONT+LEFT,
    
    BACK+LEFT,
    BACK+RIGHT,
        
    ],
    $fn=60
);    

//Loch oben    
translate(v = [-28, 0, -5]) { 
cylinder(h = 10, r1 = 2.5, r2 = 2.5,$fn=50);
}  
//Kabelschlitz
 translate(v = [-36, -1, -5]) { 
cube(size = [6,2,10]);
 }
}


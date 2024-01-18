/*
*******************************************
Objekt Info: Schlauchhalter
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

//Polygon
translate(v = [49, 0, -2]) { 
    linear_extrude(height = 4)
polygon(
 points=[
 [0,0],     // Punkt 0
 [0,11.5],  // Punkt 1
 [30,0],    // Punkt 2
 [0,-11.5]  // Punkt 3
    
],
 paths=[
 [0,1,2,3] // 4 Verbindungen
]
);
}

//Grundkoerper
difference() {
cuboid(
    [100,20,4], rounding=1,
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

//Schlauchloch oben    
rotate([0, 20, 0]) { 
translate(v = [-40, 0, -25]) { 
cylinder(h = 20, r1 = 4.5, r2 = 4.4,$fn=50);
} 
} 
//Loch fuer Gummiband
translate(v = [-15, 0, -15]) { 
cylinder(h = 20, r1 = 2.5, r2 = 2.5,$fn=50);
    }
}
//Markierung in Richtung Pflanze
translate(v = [-30, 0, 1]) { 
sphere(r = 2,$fn=50);
}
    

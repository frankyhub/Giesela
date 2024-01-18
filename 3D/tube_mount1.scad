HEIGHT   = 80; // in mm
TUBE_DIA =  3; // outer diameter of tube in mm

MARGIN = 2;
translate([0, 0, TUBE_DIA+2*MARGIN])
   cylinder(d1=5, d2=0.5, h=HEIGHT, $fn=50);

translate([0, 0, TUBE_DIA+2*MARGIN+HEIGHT])   
   sphere(d=0.5, $fn=40);

difference() {
   translate([0, 0, (TUBE_DIA+2*MARGIN)/2])
      cube([TUBE_DIA+2*MARGIN, 5, TUBE_DIA+2*MARGIN], true);
   translate([0, 0, TUBE_DIA/2+MARGIN])      
      rotate([90, 0, 0])
         translate([0, 0, -50])      
            cylinder(d=TUBE_DIA, h=100, $fn=50);
}
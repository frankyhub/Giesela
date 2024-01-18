//https://elektro.turanis.de/html/prj357/index.html
HEIGHT   = 80; // in mm
TUBE_DIA =  5; // outer diameter of tube in mm
MARGIN = 2;

translate([0, 0, TUBE_DIA+2*MARGIN])
   cylinder(d=6, h=2, $fn=50);

translate([0, -15, -12])
   scale(0.2)
      rotate([90, 0, 90])
         linear_extrude(height=20, center=true)
            import("clip_half_.svg");
translate([0, 15, -12])
   scale(0.2)
      rotate([90, 0, -90])
         linear_extrude(height=20, center=true)
            import("clip_half.svg");

difference() {
   translate([0, 0, (TUBE_DIA+2*MARGIN)/2])
      cube([TUBE_DIA+2*MARGIN, 5, TUBE_DIA+2*MARGIN], true);
   translate([0, 0, TUBE_DIA/2+MARGIN])      
      rotate([90, 0, 0])
         translate([0, 0, -50])      
            cylinder(d=TUBE_DIA, h=100, $fn=50);
}
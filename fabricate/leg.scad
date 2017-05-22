$fn=99;
difference (){
    union(){
        cylinder(h = 73, d = 18);
        cylinder(h=4,r1=12,r2=9);
    }

        translate([0,0,63])cylinder(h = 12, d = 2.8);
        translate([0,0,-1])cylinder(h = 12, d = 2.8);
}
var square = function( val ) {
  return val * val;
};

(function () {
	console.log( "Anonymous function!" );
})();

console.log( square( 10 ), " is 10 squared." );

var p1 = new Point();
var p2 = new Point( 5, -4 );

p1.print();
p2.print();

p1.x = 9.01;
p1.y = p2.y * p2.x;
p1.print();

console.test( p1 );
console.test( p2 );
console.assert( p1 instanceof Point, "p1 is not a point!" );


/*
This script should produce the following output:

Anonymous function!
100 is 10 squared.
[x=0,y=0]
[x=5,y=-4]
[x=9.01,y=-20]
X = 9.01, Y = -20
X = 5, Y = -4

*/

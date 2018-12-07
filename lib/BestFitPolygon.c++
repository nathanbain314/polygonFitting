#include "BestFitPolygon.h"
#include "PolygonFitting.h"

void test1( Polygon &R )
{
  R.addVertex(66.7695,104.821);
  R.addVertex(71.8299,114.839);
  R.addVertex(71.3801,123.594);
  R.addVertex(70.6173,126.715);
  R.addVertex(31.1714,123.369);
  R.addVertex(37.788,97.1706);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,0);
}

void test2( Polygon &R )
{
  R.addVertex(259.922,35.1728);
  R.addVertex(259.164,37.8261);
  R.addVertex(255.017,41.9732);
  R.addVertex(251.338,34.6154);
  R.addVertex(259.365,34.6154);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,0);
}

void test3( Polygon &R )
{
  R.addVertex(798.913,933.215);
  R.addVertex(854.984,975.269);
  R.addVertex(855.092,976.877);
  R.addVertex(781.283,939.972);
  R.addVertex(781.625,938.488);
  R.addVertex(784.737,936.759);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,0);
}

void test4( Polygon &R )
{
  R.addVertex( 0,0 );
  R.addVertex( 0,2 );
  R.addVertex( 2,2 );
  R.addVertex( 3,3 );
  R.addVertex( 3,0 );

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,0);
}

void test5( Polygon &R )
{
  R.addVertex( 0,0 );
  R.addVertex( 0,0.5 );
  R.addVertex( 0.5,1 );
  R.addVertex( 0.5,0 );

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,0);
}

void test6( Polygon &R )
{
  R.addVertex( 0,0 );
  R.addVertex( 0,1 );
  R.addVertex( .5,2 );
  R.addVertex( 2,2.214 );
  R.addVertex( 2.5,2.8 );
  R.addVertex( 3,3 );
  R.addVertex( 3,0 );

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,6);
  R.addEdge(6,0);
}

void test7( Polygon &R )
{
  R.addVertex( 0,0 );
  R.addVertex( 0,1 );
  R.addVertex( 1,2 );
//  R.addVertex( 0.5,0 );

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,0);
//  R.addEdge(3,0);
}

void test8( Polygon &R )
{
  R.addVertex( 0,0 );
  R.addVertex( 1,1 );
  R.addVertex( 1,0 );
  R.addVertex( 0,1 );

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,0);
}

void test9( Polygon &R )
{
  R.addVertex(876.743835449219,344.800079345703);
  R.addVertex(842.629089355469,294.587188720703);
  R.addEdge(0,1);
  R.addVertex(842.628967285156,294.587188720703);
  R.addVertex(796.933227539062,306.919525146484);
  R.addEdge(2,3);
  R.addVertex(796.933227539062,306.919464111328);
  R.addVertex(777.6513671875,384.387664794922);
  R.addEdge(4,5);
  R.addVertex(777.6513671875,384.387603759766);
  R.addVertex(820.439453125,433.9560546875);
  R.addEdge(6,7);
  R.addVertex(820.439392089844,433.956115722656);
  R.addVertex(876.743835449219,344.800079345703);
  R.addEdge(8,9);
}

void test10( Polygon &R )
{
  R.addVertex(649.219,519.982);
  R.addVertex(650.464,524.334);
  R.addEdge(0,1);
  R.addVertex(650.464,524.334);
  R.addVertex(641.651,533.226);
  R.addEdge(2,3);
  R.addVertex(641.651,533.226);
  R.addVertex(638.798,534.873);
  R.addEdge(4,5);
  R.addVertex(638.798,534.873);
  R.addVertex(636.348,535.02);
  R.addEdge(6,7);
  R.addVertex(636.348,535.02);
  R.addVertex(633.348,534.216);
  R.addEdge(8,9);
  R.addVertex(633.348,534.216);
  R.addVertex(589.431,516.693);
  R.addEdge(10,11);
  R.addVertex(589.431,516.693);
  R.addVertex(590.797,519.059);
  R.addEdge(12,13);
  R.addVertex(590.797,519.059);
  R.addVertex(606.037,527.815);
  R.addEdge(14,15);
  R.addVertex(606.037,527.815);
  R.addVertex(623.662,558.342);
  R.addEdge(16,17);
  R.addVertex(623.662,558.342);
  R.addVertex(624.04,564.637);
  R.addEdge(18,19);
  R.addVertex(624.04,564.637);
  R.addVertex(621.271,571.12);
  R.addEdge(20,21);
  R.addVertex(621.271,571.12);
  R.addVertex(601.668,589.14);
  R.addEdge(22,23);
  R.addVertex(601.668,589.14);
  R.addVertex(612.07,581.005);
  R.addEdge(24,25);
  R.addVertex(612.07,581.005);
  R.addVertex(625.726,573.121);
  R.addEdge(26,27);
  R.addVertex(625.726,573.121);
  R.addVertex(629.316,574.083);
  R.addEdge(28,29);
  R.addVertex(629.316,574.083);
  R.addVertex(644.614,579.818);
  R.addEdge(30,31);
  R.addVertex(644.614,579.818);
  R.addVertex(646.58,576.842);
  R.addEdge(32,33);
  R.addVertex(646.58,576.842);
  R.addVertex(649.926,573.068);
  R.addEdge(34,35);
  R.addVertex(649.926,573.068);
  R.addVertex(671.813,556.748);
  R.addEdge(36,37);
  R.addVertex(671.813,556.748);
  R.addVertex(688.603,550.738);
  R.addEdge(38,39);
  R.addVertex(688.603,550.738);
  R.addVertex(692.163,550.524);
  R.addEdge(40,41);
  R.addVertex(692.163,550.524);
  R.addVertex(690.113,539.085);
  R.addEdge(42,43);
  R.addVertex(690.113,539.085);
  R.addVertex(689.548,535.883);
  R.addEdge(44,45);
  R.addVertex(689.548,535.883);
  R.addVertex(690.02,529.197);
  R.addEdge(46,47);
  R.addVertex(690.02,529.197);
  R.addVertex(704.22,522.498);
  R.addEdge(48,49);
  R.addVertex(704.22,522.498);
  R.addVertex(700.498,523.605);
  R.addEdge(50,51);
  R.addVertex(700.498,523.605);
  R.addVertex(695.067,524.41);
  R.addEdge(52,53);
  R.addVertex(695.067,524.41);
  R.addVertex(665.394,522.704);
  R.addEdge(54,55);
  R.addVertex(665.394,522.704);
  R.addVertex(649.219,519.982);
  R.addEdge(56,57);
}

void test11( Polygon &R )
{
  R.addVertex(952.363903106015,391.670866833277);
  R.addVertex(951.735803520133,394.01496642805);
  R.addEdge(0,1);
  R.addVertex(951.735803520133,394.01496642805);
  R.addVertex(950.821703932769,395.863699492714);
  R.addEdge(2,3);
  R.addVertex(950.821703932769,395.863699492714);
  R.addVertex(945.239939045796,401.067799102306);
  R.addEdge(4,5);
  R.addVertex(945.239939045796,401.067799102306);
  R.addVertex(943.753839455469,401.925799106751);
  R.addEdge(6,7);
  R.addVertex(943.753839455469,401.925799106751);
  R.addVertex(937.370174146968,402.308966471025);
  R.addEdge(8,9);
  R.addVertex(937.370174146968,402.308966471025);
  R.addVertex(930.420390456209,401.017848754738);
  R.addEdge(10,11);
  R.addVertex(930.420390456209,401.017848754738);
  R.addVertex(929.697260974946,402.480351747326);
  R.addEdge(12,13);
  R.addVertex(929.697260974946,402.480351747326);
  R.addVertex(925.2816165495,406.597231246173);
  R.addEdge(14,15);
  R.addVertex(925.2816165495,406.597231246173);
  R.addVertex(924.105987065893,407.27598124969);
  R.addEdge(16,17);
  R.addVertex(924.105987065893,407.27598124969);
  R.addVertex(919.055972114675,407.579098788735);
  R.addEdge(18,19);
  R.addVertex(919.055972114675,407.579098788735);
  R.addVertex(912.513897820851,411.319013682082);
  R.addEdge(20,21);
  R.addVertex(912.51385641088,411.319234926658);
  R.addVertex(905.640389894812,411.534490156529);
  R.addEdge(22,23);
  R.addVertex(905.640389894812,411.534490156529);
  R.addVertex(904.965226055323,412.557072079823);
  R.addEdge(24,25);
  R.addVertex(904.965226055323,412.557072079823);
  R.addVertex(898.174243004194,413.946744415043);
  R.addEdge(26,27);
  R.addVertex(898.174243004194,413.946744415043);
  R.addVertex(898.381765683955,413.994387511374);
  R.addEdge(28,29);
  R.addVertex(898.381765683955,413.994387511374);
  R.addVertex(903.503239364116,417.065040103808);
  R.addEdge(30,31);
  R.addVertex(903.503239364116,417.065040103808);
  R.addVertex(904.083239367121,418.069629570463);
  R.addEdge(32,33);
  R.addVertex(904.083239367121,418.069629570463);
  R.addVertex(904.04717625186,426.12716638091);
  R.addEdge(34,35);
  R.addVertex(904.04717625186,426.12716638091);
  R.addVertex(901.365050007815,437.721587401858);
  R.addEdge(36,37);
  R.addVertex(901.365050007815,437.721587401858);
  R.addVertex(900.650460542663,438.803882138191);
  R.addEdge(38,39);
  R.addVertex(900.650460542663,438.803882138191);
  R.addVertex(921.53169582619,433.962204100925);
  R.addEdge(40,41);
  R.addVertex(921.53169582619,433.962204100925);
  R.addVertex(923.493243362374,432.829704095057);
  R.addEdge(42,43);
  R.addVertex(923.493243362374,432.829704095057);
  R.addVertex(933.402131868477,428.852402425129);
  R.addEdge(44,45);
  R.addVertex(933.402131868477,428.852402425129);
  R.addVertex(934.433481049161,429.128751601901);
  R.addEdge(46,47);
  R.addVertex(934.433481049161,429.128751601901);
  R.addVertex(936.219830233757,430.712799136129);
  R.addEdge(48,49);
  R.addVertex(936.219830233757,430.712799136129);
  R.addVertex(945.731377809061,442.657282704821);
  R.addEdge(50,51);
  R.addVertex(945.731377809061,442.657282704821);
  R.addVertex(947.950545076687,437.132429207986);
  R.addEdge(52,53);
  R.addVertex(947.950545076687,437.132429207986);
  R.addVertex(954.911184733661,432.366610750915);
  R.addEdge(54,55);
  R.addVertex(954.911184733661,432.366610750915);
  R.addVertex(956.592140039503,431.396110745886);
  R.addEdge(56,57);
  R.addVertex(956.592140039503,431.396110745886);
  R.addVertex(965.083598136786,427.987747592981);
  R.addEdge(58,59);
  R.addVertex(965.083598136786,427.987747592981);
  R.addVertex(965.967416573743,428.224566026586);
  R.addEdge(60,61);
  R.addVertex(965.967416573743,428.224566026586);
  R.addVertex(967.498235014053,429.582021330752);
  R.addEdge(62,63);
  R.addVertex(967.498235014053,429.582021330752);
  R.addVertex(975.649190353419,439.817890031339);
  R.addEdge(64,65);
  R.addVertex(975.649190353419,439.817890031339);
  R.addVertex(983.986355920905,441.661093448202);
  R.addEdge(66,67);
  R.addVertex(983.986355920905,441.661093448202);
  R.addVertex(986.00506113364,440.495593442163);
  R.addEdge(68,69);
  R.addVertex(986.00506113364,440.495593442163);
  R.addVertex(988.127864612823,441.064396913293);
  R.addEdge(70,71);
  R.addVertex(988.127864612823,441.064396913293);
  R.addVertex(995.092971585279,446.912316018603);
  R.addEdge(72,73);
  R.addVertex(995.092971585279,446.912316018603);
  R.addVertex(980.329690546813,431.483938596629);
  R.addEdge(74,75);
  R.addVertex(980.329690546813,431.483938596629);
  R.addVertex(971.710618080477,421.943267246035);
  R.addEdge(76,77);
  R.addVertex(971.710618080477,421.943267246035);
  R.addVertex(969.914618071172,418.832504001014);
  R.addEdge(78,79);
  R.addVertex(969.914618071172,418.832504001014);
  R.addVertex(970.122999686703,415.601431562596);
  R.addEdge(80,81);
  R.addVertex(970.122999686703,415.601431562596);
  R.addVertex(970.78038130456,413.148049935432);
  R.addEdge(82,83);
  R.addVertex(970.78038130456,413.148049935432);
  R.addVertex(980.978434273012,402.075595841933);
  R.addEdge(84,85);
  R.addVertex(980.978434273012,402.075595841933);
  R.addVertex(983.311506706778,400.728595834953);
  R.addEdge(86,87);
  R.addVertex(983.311506706778,400.728595834953);
  R.addVertex(979.210372433309,400.801035333687);
  R.addEdge(88,89);
  R.addVertex(979.210372433309,400.801035333687);
  R.addVertex(968.852065396442,393.961921331859);
  R.addEdge(90,91);
  R.addVertex(968.852065396442,393.961921331859);
  R.addVertex(967.662565390279,391.901646899814);
  R.addEdge(92,93);
  R.addVertex(967.662565390279,391.901646899814);
  R.addVertex(965.071081657764,384.241065455556);
  R.addEdge(94,95);
  R.addVertex(965.071081657764,384.241065455556);
  R.addVertex(964.568339795616,381.784291021457);
  R.addEdge(96,97);
  R.addVertex(964.568339795616,381.784291021457);
  R.addVertex(964.858597937576,380.701032875387);
  R.addEdge(98,99);
  R.addVertex(964.858597937576,380.701032875387);
  R.addVertex(965.927677355548,376.689239040425);
  R.addEdge(100,101);
  R.addVertex(965.927677355548,376.689239040425);
  R.addVertex(959.340804455711,382.830440502793);
  R.addEdge(102,103);
  R.addVertex(959.340804455711,382.830440502793);
  R.addVertex(957.587103016076,383.842940508039);
  R.addEdge(104,105);
  R.addVertex(957.587103016076,383.842940508039);
  R.addVertex(952.363903106015,391.670866833277);
  R.addEdge(106,107);
}

void imageInPolygon()
{
  Polygon P, P2, R;

  polygonFromAlphaImage( P2, "1.png", 2 );

  P2.makeClockwise();
  P2.center();

  test11(R);

  R.makeClockwise();

  double scale, rotation;

  Vertex offset;

  std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();

  findBestFit( P2, R, scale, rotation, offset, 10 );

std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 <<std::endl;

  cout << scale << " " << rotation << " " << offset.x << " " << offset.y << endl;

  drawImage( P2, R, scale, rotation, offset, "out.png", 5 );

  drawImage( "1.png", R, scale, rotation, offset, "out.png", 5 );
}

void RunBestFitPolygon()
{
  imageInPolygon();
}
clear all
close all

Tp = 0.2;
SSs = ss([-1,0;0,-1],[1,.1;.02,.9],[1,0;0,1],[0,0;0,0]);
SSz = c2d(SSs,Tp);
model = LTISystem('A', SSz.A, 'B', SSz.B, 'C', SSz.C, 'D', SSz.D, 'Ts', Tp);

N = 10;
Nu = 2;
model.u.min = [-1; -1];
model.u.max = [ 1;  1];
model.u.with( 'block' );
model.u.block.from = Nu;
model.u.block.to   = N;
model.y.with('reference');
model.y.reference = 'free';
model.y.penalty = QuadFunction( diag([10,10]) );
model.u.penalty = QuadFunction( diag([.1,.1]) );

ctrl = MPCController(model);
ctrl.N = N;

expmpc = ctrl.toExplicit();
expmpc.exportToC('controller','directory')

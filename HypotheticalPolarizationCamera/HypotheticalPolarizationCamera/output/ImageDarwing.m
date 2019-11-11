% Drawing DOP and AOP images
% 
% ==========================================================================
% 
% Copyright (c) 2019 - 2020, Huaju Liang and Hongyang Bai
% All rights reserved.
% 
% Redistribution and use in source and binary forms, with or without 
% modification, are permitted provided that the following conditions are met:
% 
%     * Redistributions of source code must retain the above copyright
%       notice, this list of conditions and the following disclaimer.
%     * Redistributions in binary form must reproduce the above copyright
%       notice, this list of conditions and the following disclaimer in the
%       documentation and/or other materials provided with the distribution.
%     * None of the names of the contributors may be used to endorse or promote 
%       products derived from this software without specific prior written 
%       permission.
% 
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
% ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
% WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
% DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
% DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
% (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
% LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
% ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
% (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
% SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
% ==========================================================================
% 
% 
%This file is part of an implementation of Hypothetical Polarization Camera
%which is the code of our manuscript
% 
% 
%      "Limitation of Rayleigh Sky Model for Bio-inspired Polarized Skylight Navigation in Three-dimensional Attitude Determination"
%                                     
%                                    by 
% 
%                        Huaju Liang and Hongyang Bai
%               Nanjing University of Science and Technology in Nanjing, China
% 
% 
%                         Version: 1.1, October 23, 2019
% =========================================================================
% 
% 
% 
% This code is written for drawing DOP (degree of polarization) and AOP (angle of polarization)images.
% And this code is written in MATLAB R2016b.
% 
% Usage information:
% Using the code to draw DOP and AOP images.
% --------------------------
% 
% Place the "ImageDarwing.m" file in the "output" folder of the "HypotheticalPolarizationCamera" program. 
% Then, run "ImageDarwing.m" with MATLAB R2016b after running the "HypotheticalPolarizationCamera" program. 
% Above all, "DOP.png" and "AOP.png" can be obtained.
% 
% --------------------------
% ========================================================================== 






clear;
close all;
clc;

% +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
% Read the TXT file generated hypothetical polarization camera.
% +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
fid = fopen('.\HypotheticalImages.txt');
fid_camera = textscan(fid,'%d %d %f %f');
fclose(fid);

Camera_i_x = max(fid_camera{1});
Camera_j_z = max(fid_camera{2});

Camera_PixelInterval = fid_camera{2}(2,1) - fid_camera{2}(1,1);

i_x = floor(Camera_i_x/Camera_PixelInterval);
j_z = floor(Camera_j_z/Camera_PixelInterval);

DOP = zeros(i_x,j_z);
AOP = zeros(i_x,j_z);

PixsNum = 1;
for i_x=1:Camera_PixelInterval:Camera_i_x
    for j_z=1:Camera_PixelInterval:Camera_j_z
        DOP(ceil(i_x/Camera_PixelInterval),ceil(j_z/Camera_PixelInterval)) = fid_camera{3}(PixsNum,1);
        AOP(ceil(i_x/Camera_PixelInterval),ceil(j_z/Camera_PixelInterval)) = fid_camera{4}(PixsNum,1);
        PixsNum = PixsNum +1;
    end
end



% +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
% Draw DOP image captured by hypothetical polarization camera.
% +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
figure(1);
plotHandles = pcolor(DOP);
set(gca,'position',[-0.1,0.05,0.9,0.9]);
mymap=[cool;spring]; 
colormap(mymap);
hBar = colorbar('FontSize',22,'YTick',[0 0.2 0.4 0.6 0.8 1],'YTickLabel',{'0', '0.2', '0.4', '0.6', '0.8', '1'});
set(hBar,'position',[0.7,0.1,0.05,0.8]);
axis equal;
set(plotHandles , 'EdgeColor' , 'none');
axis off;
caxis([0,1]);
view(90,-90);
set(get(hBar,'title'),'string','DOP','Rotation',90.0,'Position',[85,125]);
set(0,'defaultfigurecolor','w');
saveas(gcf,'DOP','png');



% +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
% Draw AOP image captured by hypothetical polarization camera.
% +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
figure(2);
plotHandles = pcolor(AOP);
set(gca,'position',[-0.1,0.05,0.9,0.9]);
colormap jet;
hBar = colorbar('FontSize',22,'YTick',[-90 -45 0 45 90],'YTickLabel',{'-90','-45','0','45','90'});
set(hBar,'position',[0.7,0.1,0.05,0.8]);
axis equal;
set(plotHandles , 'EdgeColor' , 'none');
axis off;
caxis([-90,90]);
view(90,-90);
set(get(hBar,'title'),'string','AOP (deg)','Rotation',90.0,'Position',[85,125]);
set(0,'defaultfigurecolor','w');
saveas(gcf,'AOP','png');






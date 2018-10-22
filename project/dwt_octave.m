clear;
pkg load image;

% % input
img = imread('pics/impact51.jpg');
level = 5;
scale = 1024;

subplot(2,3,1);
imshow(img);
title('Original');

% % image pre-process
%R = rgb2gray(img);
R = img(:, :, 1);
% R = histeq(R);
subplot(2,3,2);
imshow(R);
title('Equalized');

[h,w] = size(R);
R = double(imresize(R,[scale scale]));

% % 2-D DWT
s = scale;
for i = 1:level
    R(1:s, 1:s) = [R(1:s, 1:2:s) + R(1:s, 2:2:s)   R(1:s, 1:2:s) - R(1:s, 2:2:s)];
    R(1:s, 1:s) = [R(1:2:s, 1:s) + R(2:2:s, 1:s);   R(1:2:s, 1:s) - R(2:2:s, 1:s)];
    s = s/2;
end

% % 5-th level
R(1:s, 1:s) = zeros(s,s);
R(1:2*s, 1:2*s) = R(1:2*s, 1:2*s) * 2;

% % inverse 2-D DWT
for i = 1:level
    s = 2*s;
    Rt(1:2:s, 1:s) = (R(1:1:s/2, 1:s)+R(s/2+1:1:s, 1:s))/2;
    Rt(2:2:s, 1:s) = (R(1:1:s/2, 1:s)-R(s/2+1:1:s, 1:s))/2;
    R(1:s, 1:2:s) = (Rt(1:s,1:1:s/2)+Rt(1:s, s/2+1:1:s))/2;
    R(1:s, 2:2:s) = (Rt(1:s,1:1:s/2)-Rt(1:s, s/2+1:1:s))/2;
end

% % 
R=imresize(R,[h w]);

R(:,:) = -R(:,:);
R = uint8(R);

subplot(2,3,3);
imshow(R);
title('DWT');

R=im2bw(R,0.1);

subplot(2,3,4);
imshow(R);
title('1-bit');

R = imerode(R, strel('diamond', 3));
R = imdilate(R, strel('diamond', 3));

R = imdilate(R, strel('diamond', 5));
R = imerode(R, strel('diamond', 5));

subplot(2,3,5);
imshow(R);
title('morphological analyzed');
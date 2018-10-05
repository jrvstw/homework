clear;
img = imread('water1384.jpg');
layer = 7;
scale = 2048;

R = rgb2gray(img);
[h,w] = size(R);
s = scale;
R = double(imresize(R,[s s]));
for i = 1:layer
    R(1:s, 1:s) = [R(1:s, 1:2:s) + R(1:s, 2:2:s)   R(1:s, 1:2:s) - R(1:s, 2:2:s)];
    R(1:s, 1:s) = [R(1:2:s, 1:s) + R(2:2:s, 1:s);   R(1:2:s, 1:s) - R(2:2:s, 1:s)];
    s = s/2;
end
R(1:s, 1:s) = zeros(s,s);

for i = 1:layer
    s = 2*s;
    Rt(1:2:s, 1:s) = (R(1:1:s/2, 1:s)+R(s/2+1:1:s, 1:s))/2;
    Rt(2:2:s, 1:s) = (R(1:1:s/2, 1:s)-R(s/2+1:1:s, 1:s))/2;
    R(1:s, 1:2:s) = (Rt(1:s,1:1:s/2)+Rt(1:s, s/2+1:1:s))/2;
    R(1:s, 2:2:s) = (Rt(1:s,1:1:s/2)-Rt(1:s, s/2+1:1:s))/2;
end
R=imresize(uint8(R),[h w]);
imshow(R)
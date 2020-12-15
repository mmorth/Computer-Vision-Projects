clear all;
close all;
load yalefaces
[h, w, n] = size(yalefaces);
d = h * w;
% vectorize images
x = reshape(yalefaces, [d n]);
x = double(x);
% subtract mean
mean_matrix = mean(x, 2);
x = bsxfun(@minus, x, mean_matrix);
% calculate covariance
s = cov(x');
% obtain eigenvalue & eigenvector
[V, D] = eig(s);
eigval = diag(D);
% sort eigenvalues in descending order
eigval = eigval(end: - 1:1);
V = fliplr(V);
% show mean and 1st through 15th principal eigenvectors
figure, subplot(4, 4, 1)
imagesc(reshape(mean_matrix, [h, w]))
colormap gray
for i = 1:15
    subplot(4, 4, i + 1)
    imagesc(reshape(V(:, i), h, w))
end
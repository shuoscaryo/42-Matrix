Matrix<float> projection(float fov, float ratio, float near, float far)
{
	// alfa is YZ angle, beta is XZ angle
	float tanBeta = tan(fov/2);
	float tanAlfa = ratio * tanBeta;
	// Z projection ratios
    float K = far / (near - far);
    float L = near * far / (near - far);
	Matrix<float> output = {
		{1/tanAlfa, 0, 0, 0},
		{0, 1/tanBeta, 0, 0},
		{0, 0, K, L},
		{0, 0, -1, 0}
	};
	return output;
}

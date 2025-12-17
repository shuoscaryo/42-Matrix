template <typename V>
V lerp(V u, V v, float t)
{
	return u + (v - u) * t;
}

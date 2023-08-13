#include "stdafx.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <sstream>

std::random_device Utils::randomDevice;
std::mt19937 Utils::gen(Utils::randomDevice());

int Utils::RandomRange(int min, int maxExclude)
{
	std::uniform_int_distribution<int> dist(min, maxExclude - 1);
	return dist(gen);
}

float Utils::RandomRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return (float)dist(gen);
}

sf::Vector2f Utils::RandomOnCircle(float radius)
{
	sf::Vector2f result(RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f));
	result = Normalize(result) * radius;
	return result;
}

sf::Vector2f Utils::RandomInCircle(float radius)
{
	return RandomOnCircle(radius) * RandomValue();
}

float Utils::RandomValue()
{
	return RandomRange(0.0f, 1.0f);
}

const sf::Vector2f& Utils::SetOrigin(sf::Sprite& sprite, Origins origin)
{
	return SetOrigin(sprite, origin, sprite.getLocalBounds());
}

const sf::Vector2f& Utils::SetOrigin(sf::Text& text, Origins origin)
{
	return SetOrigin(text, origin, text.getLocalBounds());
}

const sf::Vector2f& Utils::SetOrigin(sf::Shape& shape, Origins origin)
{
	return SetOrigin(shape, origin, shape.getLocalBounds());
}

const sf::Vector2f& Utils::SetOrigin(sf::Transformable& transformable, Origins origin, const sf::FloatRect& rect)
{
	sf::Vector2f originPos(rect.width, rect.height);
	originPos.x *= ((int)origin % 3) * 0.5f;
	originPos.y *= ((int)origin / 3) * 0.5f;

	transformable.setOrigin(originPos);
	return originPos;
}

float Utils::Clamp(float v, float min, float max)
{
	return std::max(std::min(v, max), min);
}

int Utils::Clamp(int v, int min, int max)
{
	return std::max(std::min(v, max), min);
}

sf::Vector2f Utils::Clamp(const sf::Vector2f& v, const sf::Vector2f& min, const sf::Vector2f& max)
{
	sf::Vector2f result;
	result.x = Clamp(v.x, min.x, max.x);
	result.y = Clamp(v.y, min.y, max.y);
	return result;
}

float Utils::Lerp(float a, float b, float t, bool clamping)
{
	if (clamping)
	{
		t = Clamp(t, 0.0f, 1.0f);
	}
	return a + (b - a) * t;
}

sf::Vector2f Utils::Lerp(sf::Vector2f a, sf::Vector2f b, float t, bool clamping)
{
	if (clamping)
	{
		t = Clamp(t, 0.0f, 1.0f);
	}
	return a + (b - a) * t;
}

sf::Color Utils::Lerp(sf::Color a, sf::Color b, float t, bool clamping)
{
	sf::Color result;
	if (clamping)
	{
		t = Clamp(t, 0.0f, 1.0f);
	}
	result.r = a.r + (b.r - a.r) * t;
	result.g = a.g + (b.g - a.g) * t;
	result.b = a.b + (b.b - a.b) * t;
	result.a = a.a + (b.a - a.a) * t;
	return result;
}

const sf::Vector2f Utils::Normalize(const sf::Vector2f& vector)
{
	float mag = Magnitude(vector);
	if (mag == 0.f)
	{
		return vector;
	}
	return vector / mag;
}

float Utils::Magnitude(const sf::Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Utils::SqrMagnitude(const sf::Vector2f& vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p2 - p1);
}



float Utils::Angle(const sf::Vector2f& start, const sf::Vector2f& end)
{
	return Angle(Normalize(end - start));
}

float Utils::Angle(const sf::Vector2f& direction)
{
	return atan2(direction.y, direction.x) * (180.0f / M_PI);
}

sf::Vector2f Utils::RotateWithPivot(const sf::Vector2f& pivot, const sf::Vector2f& target, const float& rotation)
{
	float distance = Utils::Distance(target, pivot);
	sf::Vector2f direction = Utils::Normalize(target - pivot);

	float radian = (rotation) * M_PI / 180;

	sf::Vector2f rightDirection = {1.0f, 0.0f};

	sf::Vector2f result;
	result.x = cos(radian) * direction.x - sin(radian) * direction.y;
	result.y = sin(radian) * direction.x + cos(radian) * direction.y;

	return pivot + (result * distance);
}

/// <summary>
/// Vector의 내적
/// </summary>
sf::Vector2f Utils::DotProuct(const sf::Vector2f& axis, const sf::Vector2f& target)
{
	return (axis.x * target.x + axis.y * target.y) * axis;
}

/// <summary>
/// Vector의 외적
/// </summary>
float Utils::CrossProduct(const sf::Vector2f& vector, const sf::Vector2f& other)
{
	return vector.x * other.y - vector.y * other.x;
}

 ///<summary>
 ///Line의 접점
 ///</summary>
sf::Vector2f Utils::Intersection(const sf::Vector2f& c1, const sf::Vector2f& c2, const sf::Vector2f& d1, const sf::Vector2f& d2)
{
	/*
	두 점 A(x1, y1), B(x2, y2)을 잇는 직선의 방정식
	y = ax + b (a : 기울기 = y증가량/x증가량, b : 상수)
	a = (y2-y1)/(x2-x1)
	y = (y2-y1)/(x2-x1)x + b
	b = y - (y2-y1)/(x2-x1)x
	b = y1 - (y2-y1)/(x2-x1)x1

	!!!!! y = (y2-y1)/(x2-x1)x + (y1 - (y2-y1)/(x2-x1)x1) !!!!!

	방정식 1 : y = a1x + b1
	방정식 2 : y = a2x + b2
	(a1-a2)x = (b2-b1)
	x = (b2-b1)/(a1-a2)
	방정식 1에 대입하면
	y = a1((b2-b1)/(a1-a2)) + b1
	 
	교점의 좌표 (x,y) = ( (b2-b1)/(a1-a2), a1((b2-b1)/(a1-a2)) + b1)
	 */

	float a1, b1, a2, b2;
	a1 = (c2.y - c1.y) / (c2.x - c1.x);
	//b1 = c1.y - (((c2.y - c1.y) / (c2.x - c1.x))*c1.x);
	b1 = c1.y - (a1 * c1.x);
	//cout << "test:x:" << intersection.x << endl;

	a2 = (d2.y - d1.y) / (d2.x - d1.x);
	//b2 = d1.y - (((d2.y - d1.y) / (d2.x - d1.x))*d1.x);
	b2 = d1.y - (a2 * d1.x);

	if (a1 == a2) return { 0.0f, 0.0f };//평행이나 일치인 경우

	sf::Vector2f intersection;
	intersection.x = (b2 - b1) / (a1 - a2);
	intersection.y = a1 * (intersection.x) + b1;
	std::cout << "test:x:" << intersection.x << std::endl;
	std::cout << "test:y:" << intersection.y << std::endl;
}

//sf::Vector2f Utils::Intersection(const sf::Vector2f& lineAStart, const sf::Vector2f& lineAEnd, const sf::Vector2f& lineBStart, const sf::Vector2f& lineBEnd)
//{
//	float det = Utils::CrossProduct((lineAEnd - lineAStart), (lineBEnd - lineBStart));
//	if (det == 0) // parallel or coincident lines
//	{
//		return sf::Vector2f(0, 0); // arbitrary value
//	}
//	float t = Utils::CrossProduct((lineBStart - lineAStart), (lineBEnd - lineBStart)) / det;
//	float u = Utils::CrossProduct((lineBStart - lineAStart), (lineAEnd - lineAStart)) / det;
//	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) // intersection point is within both line segments
//	{
//		sf::Vector2f result = lineAStart + (lineAEnd - lineAStart) * t; // same as lineBStart + (lineBEnd - lineBStart) * u
//		return result;
//	}
//	else // intersection point is outside one or both line segments
//	{
//		return sf::Vector2f(0, 0); // arbitrary value
//	}
//}

sf::Vector2f Utils::RectNormal(sf::Rect<float> base, sf::Rect<float> target)
{
	sf::Vector2f baseCenter(base.left + base.width * 0.5f, base.top + base.height * 0.5f);
	sf::Vector2f targetCenter(target.left + target.width * 0.5f, target.top + target.height * 0.5f);
	sf::Vector2f val = (targetCenter - baseCenter);
	val.x /= base.width + target.width;
	val.y /= base.height + target.height;

	if (abs(val.x) > abs(val.y))
	{
		return val.y > 0.0f ? sf::Vector2f(0.0f, 1.0f) : sf::Vector2f(0.0f, -1.0f);
	}
	else
	{
		return val.x > 0.0f ? sf::Vector2f(1.0f, 0.0f) : sf::Vector2f(-1.0f, 0.0f);
	}
}

std::string Utils::ToString(int value, std::string format)
{
	std::string toString = std::to_string(value);
	bool hasMinusSign = false;
	if (Utils::Contains(std::to_string(value), '-'))
	{
		hasMinusSign = true;
		remove(toString.begin(), toString.end(), '-');
	}
	std::string formatRealPart;
	std::string formatDecimalPart;
	if (Utils::Contains(format, '.'))
	{
		std::vector<std::string> formatResult = Split(format, '.');
		formatRealPart = formatResult[0];
		formatDecimalPart = formatResult[1];
	}
	else
	{
		formatRealPart = format;
	}

	std::stringstream ss;
	if (hasMinusSign)
	{
		ss << '-';
	}
	for (int i = 0; i + toString.size() < formatRealPart.size(); i++)
	{
		if (format.c_str()[i] == '0')
		{
			ss << '0';
		}
	}
	ss << toString;

	if (formatDecimalPart.size() > 0)
	{
		ss << '.';
		for (int i = 0; i < formatDecimalPart.size(); i++)
		{
			if (format.c_str()[i] == '0')
			{
				ss << '0';
			}
		}
	}
	return ss.str();
}

std::string Utils::ToString(float value, std::string format)
{
	std::string temp = std::to_string(value);
	std::vector<std::string> result = Utils::Split(temp, '.');
	std::string realPart = result[0];
	std::string decimalPart = result[1];
	//TODO
	return nullptr;
}

std::vector<std::string> Utils::Split(std::string input, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(input);
	std::string temp;

	while (getline(ss, temp, delimiter)) {
		result.push_back(temp);
	}

	return result;
}

bool Utils::Contains(const std::string& str, const char& c)
{
	std::size_t found = str.find(c);
	return found != std::string::npos;
}
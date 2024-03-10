
#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>
#include <cmath>

class Vector2
{
public:

    float x;
    float y;

    /**
     * Constructs a new Vector2 object.
     *
     * @param x The x value of the vector.
     * @param y The y value of the vector.
     */
    explicit Vector2(float x, float y);

    /**
     * constructs a new Vector2 object.
     *
     * @param xy The x and y value of the vector. Default value is 0 if not provided.
     */
    explicit Vector2(float xy = 0);

    /**
     *
     * Checks if two vectors are equal. The function compares the x and value of both vectors.
     *
     * @param other The other vector to compare to.
     * @return true if the two vectors have the same x and y value, false otherwise.
     */
    bool operator==(const Vector2& other) const;

    /**
     *
     * Checks if two vectors are not equal. The function compares the x and value of both vectors.
     *
     * @param other The other vector to compare to.
     * @return true if the two vectors have not the same x or y value, false otherwise.
     */
    bool operator!=(const Vector2& other) const;

    /**
     * Adds two vectors.
     *
     * @param other The other vector to add to.
     * @return The addition of the two vectors.
     */
    Vector2 operator+(const Vector2& other) const;

    /**
     * Adds two vectors
     *
     * @param other the other vector to add to.
     * @return The addition of the two vectors.
     */
    Vector2 & operator+=(const Vector2& other);

    /**
     * Subtracts two vectors.
     *
     * @param other the other vector to subtract to.
     * @return the subtraction of the two vectors.
     */
    Vector2 operator-(const Vector2& other) const;

    /**
     * Calculates the scalar products of two vectors.
     *
     * @param other the other vector to multiply to
     * @return the scalar product of the two vectors.
     */
    float operator*(const Vector2& other) const;

    /**
     * Multiplies the vector with a given number.
     *
     * @param number The number to multiply the vector to.
     * @return The result of the multiplication with a vector and a number.
     */
    Vector2 operator*(const float& number) const;

    /**
     * Calculates the distance between two vectors.
     *
     * @param vector_1 the first vector for distance calculation
     * @param vector_2 the second vector for distance calculation
     * @return distance between two vectors
     */
    static float distance(Vector2& vector_1, Vector2& vector_2);

    /**
     * Multiplies the vector with a given number.
     *
     * @param number The number to multiply the vector to.
     * @return The result of the multiplication with a vector and a number.
     */
    Vector2 multiply(float number) const;


    /**
     * Clamps a vector.
     * @return Normalized vector.
     */
    Vector2 clamp() const;

    /**
     * Called to get the vector as string information. Used to print the vector values.
     * @return values of the vector as a string.
     */
    std::string to_string() const;




};

#endif

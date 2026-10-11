#pragma once
#include "../math/Math.h"
#include "../renderer/ICanvas.h"

/// <summary>
/// rozhrani tvar pro reprezentaci geometrickeho objektu ve 2D
/// umoznuje tvar transformovat pomoci transformacni matice a vykreslit
/// </summary>
class IShape {
public:
	/// <summary>
	/// virtualni destruktor
	/// </summary>
	virtual ~IShape() = default;

	/// <summary>
	/// transformuje objekt vynasobenim transformacni matici
	/// </summary>
	/// <param name="m">transformacni matice 3x3</param>
	virtual void transform(const Matrix3x3& m) = 0;

	/// <summary>
	/// vykresli objekt na platno
	/// </summary>
	/// <param name="canvas">platno</param>
	virtual void draw(ICanvas& canvas) const = 0;
};
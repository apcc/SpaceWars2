# include "./FontP.hpp"


RectF DrawableStringP::draw(Arg::Args arg, Vec2 pos, ColorF color, double lineHeight) const {
	double w = region(lineHeight).w;
	double h = region(lineHeight).h;

	switch (arg) {
	case Arg::topLeft:
		break;
	case Arg::topRight:
		pos.moveBy(-w, 0);
		break;
	case Arg::bottomLeft:
		pos.moveBy(0, -h);
		break;
	case Arg::bottomRight:
		pos.moveBy(-w, -h);
		break;
	case Arg::topCenter:
		pos.moveBy(-w * 0.5, 0);
		break;
	case Arg::bottomCenter:
		pos.moveBy(-w * 0.5, -h);
		break;
	case Arg::leftCenter:
		pos.moveBy(0, -h * 0.5);
		break;
	case Arg::rightCenter:
		pos.moveBy(-w, -h * 0.5);
		break;
	case Arg::center:
		pos.moveBy(-w * 0.5, -h * 0.5);
		break;
	default:
		break;
	}

	return DrawableString::draw(pos, color, lineHeight);
}


RectF FontP::draw(const String& text, Arg::Args arg, Vec2 pos, ColorF color, double lineHeight) const {
	double w = region(text, lineHeight).w;
	double h = region(text, lineHeight).h;

	switch (arg) {
	case Arg::topLeft:
		break;
	case Arg::topRight:
		pos.moveBy(-w, 0);
		break;
	case Arg::bottomLeft:
		pos.moveBy(0, -h);
		break;
	case Arg::bottomRight:
		pos.moveBy(-w, -h);
		break;
	case Arg::topCenter:
		pos.moveBy(-w * 0.5, 0);
		break;
	case Arg::bottomCenter:
		pos.moveBy(-w * 0.5, -h);
		break;
	case Arg::leftCenter:
		pos.moveBy(0, -h * 0.5);
		break;
	case Arg::rightCenter:
		pos.moveBy(-w, -h * 0.5);
		break;
	case Arg::center:
		pos.moveBy(-w * 0.5, -h * 0.5);
		break;
	default:
		break;
	}

	return Font::draw(text, pos, color, lineHeight);
}

FontP::operator Font() const {
	return Font(this->size(), this->name(), this->style());
}

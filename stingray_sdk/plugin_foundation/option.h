#pragma once

namespace stingray_plugin_foundation {

	// A class that can optionally hold a value.
	template <class T>
	class Option
	{
		bool _has_value;
		T _value;

		Option(bool has_value, const T &value) : _has_value(has_value), _value(value) {}

	public:
		// Initializes the object to hold no value.
		Option() : _has_value(false), _value() {}

		// Initializes the object to hold the specified value.
		Option(const T &value) : _has_value(true), _value(value) {}

		// Static constructor that returns an Option<T> object with no value.
		static Option<T> none() {return Option<T>();}

		// Static constructor that returns an Option<T> object with the specified value.
		static Option<T> some(const T &value) {return Option<T>(true, value);}

		// True if the object has a value.
		bool is_some() const {return _has_value;}

		// True if the object doesn't have a value.
		bool is_none() const {return !_has_value;}

		// Returns the object's value.
		const T &value() const {
			XASSERT(is_some(), "Cannot obtain value from a none Option<T>.");
			return _value;
		}
	};

}

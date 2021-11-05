#ifndef PIN_H_
#define PIN_H_

class Pin {
public:
	virtual ~Pin() {}
	virtual void set(bool value = true) const = 0;
	virtual void clear() const = 0;
	virtual bool get() const = 0;
	virtual void toggle() const = 0;
};

#endif /* PIN_H_ */

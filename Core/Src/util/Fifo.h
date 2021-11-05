#ifndef FIFO_H_
#define FIFO_H_

template<class T, unsigned COUNT=256>
class Fifo
final {
	public:
		Fifo();
		~Fifo();
		bool put(T elem);
		T get();
		T peek();
		bool is_empty();
		bool is_full();
		void clear();
	private:
		volatile T arr[COUNT];
		volatile unsigned head;
		volatile unsigned tail;
		const unsigned size = COUNT;
	};

	template<class T, unsigned COUNT>
	Fifo<T, COUNT>::Fifo() :
			arr(), head(0), tail(0) {
	}

	template<class T, unsigned COUNT>
	Fifo<T, COUNT>::~Fifo() {
	}

	template<class T, unsigned COUNT>
	bool Fifo<T, COUNT>::put(T elem) {
		if (this->is_full())
			return false;
		unsigned new_tail = this->tail + 1;
		if (new_tail >= this->size)
			new_tail = 0;
		this->arr[this->tail] = elem;
		this->tail = new_tail;
		return true;
	}

	template<class T, unsigned COUNT>
	T Fifo<T, COUNT>::get() {
		if (this->is_empty())
			return -1;
		unsigned new_head = this->head + 1;
		if (new_head >= this->size)
			new_head = 0;
		T data = this->arr[this->head];
		this->head = new_head;
		return data;
	}

	template<class T, unsigned COUNT>
	inline bool Fifo<T, COUNT>::is_empty() {
		return this->tail == this->head;
	}

	template<class T, unsigned COUNT>
	inline T Fifo<T, COUNT>::peek() {
		if (this->is_empty())
			return -1;
		T data = this->arr[this->head];
	}

	template<class T, unsigned COUNT>
	inline bool Fifo<T, COUNT>::is_full() {
		unsigned new_tail = this->tail + 1;
		if (new_tail >= this->size)
			new_tail = 0;
		return (new_tail == this->head) ? true : false;
	}

	template<class T, unsigned COUNT>
	inline void Fifo<T, COUNT>::clear() {
		this->head = 0;
		this->tail = 0;
	}

#endif /* FIFO_H_ */

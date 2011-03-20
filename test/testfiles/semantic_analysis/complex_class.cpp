namespace n
{
	namespace n2
	{
		class base1
		{
		};
	}
}

class base2
{
};

class base3
{
};

class test: public n::n2::base1, virtual base2, protected virtual base3
{
	public:
		test(const test& t);

		explicit
		test(int i);

		virtual
		~test();

		void*
		operator new[](long unsigned int, void*);

		void
		operator delete[](void*);

		const test&
		operator=(const test& t);

		bool
		operator==(const test& t) const;

		operator int() const;

		virtual
		void
		pure_virtual() = 0;

		static
		bool
		static_function();

	protected:
		void
		update()
		{
		}

	public:
		inline
		int
		value() const;

	private:
		static const bool b = false;
		int value_;
};

test::test(int)
{
}

test::test(const test&)
{
}

test::~test()
{
}

const test&
test::operator=(const test& rhs)
{
	value_ = rhs.value_;
	return *this;
}

bool
test::operator==(const test& rhs) const
{
	return value_ == rhs.value_;
}

void*
test::operator new[](long unsigned int, void*)
{
	return 0;
}

void
test::operator delete[](void*)
{
}

test::operator int() const
{
	return value_;
}

bool
test::static_function()
{
	return b;
}

int
test::value() const
{
	return value_;
}

void
test::pure_virtual()
{
}


#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

string add(const string& a, const string& b) {
	if ("0" == a)
		return b;

	if ("0" == b)
		return a;

	auto ra = string{ a };
	reverse(ra.begin(), ra.end());

	auto rb = string{ b };
	reverse(rb.begin(), rb.end());

	auto na = static_cast<int>(ra.length());
	auto nb = static_cast<int>(rb.length());

	if (na < nb) {
		auto temp = string{ ra };
		ra = rb;
		rb = temp;

		auto ntemp = int{ na };
		na = nb;
		nb = ntemp;
	}

	ostringstream oss{};
	auto carry = bool{ false };
	for (int i = 0; i < nb; ++i) {
		const auto& ba = ra[i];
		const auto& bb = rb[i];

		if ('0' == ba) {
			if ('0' == bb) {
				if (carry) {
					oss << "1";
				}
				else {
					oss << "0";
				}

				carry = false;
			}
			else {
				if (carry) {
					oss << "0";
					carry = true;
				}
				else {
					oss << "1";
					carry = false;
				}
			}
		}
		else {
			if ('0' == bb) {
				if (carry) {
					oss << "0";
					carry = true;
				}
				else {
					oss << "1";
					carry = false;
				}

			}
			else {
				if (carry) {
					oss << "1";
				}
				else {
					oss << "0";
				}

				carry = true;
			}
		}
	}

	for (int i = nb; i < na; ++i) {
		const auto& ba = ra[i];
		if ('0' == ba) {
			if (carry) {
				oss << "1";
			}
			else {
				oss << "0";
			}

			carry = false;
		}
		else {
			if (carry) {
				oss << "0";
				carry = true;
			}
			else {
				oss << "1";
				carry = false;
			}
		}
	}

	if (carry) {
		oss << "1";
	}

	auto result = static_cast<string>(oss.str());
	reverse(result.begin(), result.end());

	return result;
}

string mult(const string& a, const string& b) {
	auto result = string{ "0" };
	auto t = string{ a };

	auto n = static_cast<int>(b.length());
	for (int i = n - 1; 0 <= i; --i) {
		if ('1' == b[i]) {
			result = add(result, t);
		}

		t += "0";
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	string a, b;
	cin >> a >> b;

	cout << mult(a, b);

	return 0;
}
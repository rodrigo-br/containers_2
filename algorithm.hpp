#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace ft {

template <typename InputIt1, typename InputIt2>
inline bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	while (first1 != last1) {
		if (!(*first1 == *first2)) {
			return (false);
		}
		first1++;
		first2++;
	}
	return (true);
}

template <typename InputIt1, typename InputIt2, typename Compare>
inline bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
									Compare comp) {
	while (first1 != last1) {
		if (!comp(*first1, *first2)) {
			return (false);
		}
		first1++;
		first2++;
	}
	return (true);
}

template <typename InputIt1, typename InputIt2>
inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
																		InputIt2 first2, InputIt2 last2) {
	for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
		if (*first1 < *first2) {
			return (true);
		}
		if (*first2 < *first1) {
			return (false);
		}
	}
	return ((first1 == last1) && (first2 != last2));
}

template <typename InputIt1, typename InputIt2, typename Compare>
inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
																		InputIt2 first2, InputIt2 last2,
																		Compare comp) {
	for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
		if (comp(*first1, *first2)) {
			return (true);
		}
		if (comp(*first2, *first1)) {
			return (false);
		}
	}
	return ((first1 == last1) && (first2 != last2));
}

}

#endif

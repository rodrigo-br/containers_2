#ifndef CONTAINER_H
#define CONTAINER_H

namespace ft {
#define ALLOC typename Alloc
	template < class Type, class Alloc,
			class Ref		=	ALLOC::reference,
			class ConstRef	=	ALLOC::const_reference,
			class Ptr		=	ALLOC::pointer,
			class ConstPtr	=	ALLOC::const_pointer,
			class Dif		=	ALLOC::difference_type,
			class Size		=	ALLOC::size_type >
	struct Container {
		typedef Type			value_type;
		typedef Alloc			allocator_type;
		typedef Ref				reference;
		typedef ConstRef		const_reference;
		typedef Ptr				pointer;
		typedef ConstPtr		const_pointer;
		typedef Dif				difference_type;
		typedef Size			size_type;
	};//struct Container

#define IMPORT_TYPE(TYPE) typedef typename CONTAINER::TYPE TYPE

};//namespace ft

#endif
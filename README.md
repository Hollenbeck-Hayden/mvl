# mvl
Mathematical Vector Library in C++

Current Implementation Plan:
The entire project is based of the Matrix class. Vector and SMatrix classes
are just typedefs of the Matrix class to the appropriate restrictions. Methods
specific to these objects will be declared in the namespace scope. Thus conversion
is merely a renaming for the convenience of the user, rather than actual
compile time changing of the interface.

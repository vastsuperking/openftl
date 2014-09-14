#ifndef SUTILS_H
#define SUTILS_H

// finds the substring of the string from start to end
char *substring(const char *str, size_t start, size_t end);
// returns an array of strings terminated by a string containing only a null character
char **split(const char *str, const char *delimeters);
// returns the frequency of a regex in the string
unsigned int frequency(const char *str, const char *regex);
// returns a new char * with all the regex's replaced by the replacement string
char *replace_all(const char *str, const char *regex, const char *replacement);

#endif

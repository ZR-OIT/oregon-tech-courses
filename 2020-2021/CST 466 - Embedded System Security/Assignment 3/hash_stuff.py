import hashlib

read_file = open("infile.txt", 'r')
read_lines = read_file.readlines()
read_file.close()

write_file = open("outfile.txt", 'w')

for line in read_lines:
    string = line.strip()
    encoded_string = string.encode()
    print(hashlib.md5(encoded_string).hexdigest(), "//MD5 for", string, file = write_file)
    print(hashlib.sha1(encoded_string).hexdigest(), "//SHA1 for", string, file = write_file)

write_file.close()
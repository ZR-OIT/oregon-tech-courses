from Crypto.Cipher import AES

key = b"2B7E151628AED2A6ABF7158809CF4F3C"
iv = b"ABCDEFGHIJKLMNOP"
message = b"Iaintgoingdownforthis.Youainttakinmealive"

cipher = AES.new(key, AES.MODE_CFB, iv)
ciphertext = cipher.encrypt(message)
print(ciphertext)
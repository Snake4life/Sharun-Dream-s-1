#include <Dream/Dream.hpp>

#include <vector>

using namespace Crypt;

bool teraCrypt_version_Key_init = false;
ushort teraCrypt_version_Key_Tcount = 0;
std::vector<short*> teraCrypt_version_Key;
short teraCrypt_version_Key_tmp[][3] = {
	{31, 17, 79},
	{67, 29, 41},
	{-1, -1, -1}
};

ushort get_teraCrypt_version()
{
	return teraCrypt_version_Key.size();
}

void Add_teraCrypt_version(short k0, short k1, short k2)
{
	if (!teraCrypt_version_Key_init) {
		for ( teraCrypt_version_Key_Tcount=0; teraCrypt_version_Key_tmp[teraCrypt_version_Key_Tcount][0] != -1
						   || teraCrypt_version_Key_tmp[teraCrypt_version_Key_Tcount][1] != -1
						   || teraCrypt_version_Key_tmp[teraCrypt_version_Key_Tcount][2] != -1 ; teraCrypt_version_Key_Tcount++)
			teraCrypt_version_Key.push_back(teraCrypt_version_Key_tmp[teraCrypt_version_Key_Tcount]);
		teraCrypt_version_Key_init = true;
	}
	if (k0 != -1 || k1 != -1 || k2 != -1) {
		short *value = new short[3];
		value[0] = k0;
		value[1] = k1;
		value[2] = k2;
		teraCrypt_version_Key.push_back(value);
	}
}

void Free_teraCrypt_version()
{
	while (teraCrypt_version_Key.size()) {
		if (teraCrypt_version_Key.size() > teraCrypt_version_Key_Tcount)
			delete teraCrypt_version_Key.back();
		teraCrypt_version_Key.pop_back();
	}
	teraCrypt_version_Key_init = false;
	teraCrypt_version_Key_Tcount = 0;
}

Session::Session(const char *CKey1, const char *CKey2, const char *SKey1, const char *SKey2, unsigned char version)
{
	byte TmpKey1[128], TmpKey2[128];
	Encryptor = new Cryptor();
	Decryptor = new Cryptor();
	memcpy(ClientKey1, CKey1, 128);
	memcpy(ClientKey2, CKey2, 128);
	memcpy(ServerKey1, SKey1, 128);
	memcpy(ServerKey2, SKey2, 128);

	ShiftKey(TmpKey1, ServerKey1, teraCrypt_version_Key[version][0], true);
	XorKey(TmpKey2, TmpKey1, 128, ClientKey1, 128);

	ShiftKey(TmpKey1, ClientKey2, teraCrypt_version_Key[version][1], false);
	XorKey(DecryptKey, TmpKey1, 128, TmpKey2, 128);

	Decryptor->GenerateKey(DecryptKey);

	ShiftKey(EncryptKey, ServerKey2, teraCrypt_version_Key[version][2], true);
	Decryptor->ApplyCryptor(EncryptKey, 128);

	Encryptor->GenerateKey(EncryptKey);
}

Session::~Session()
{
	delete Encryptor;
	delete Decryptor;
}

void Session::Encrypt(byte *data, int length)
{
	Encryptor->ApplyCryptor(data, length);
}

void Session::Decrypt(byte *data, int length)
{
	Decryptor->ApplyCryptor(data, length);
}

void Session::XorKey(byte *result, byte *key1, int Length1, byte *key2, int Length2)
{
	int Length = Length1 < Length2 ? Length1 : Length2;
	for (int i = 0; i < Length; i++)
		result[i] = (byte) (key1[i] ^ key2[i]);
}

void Session::ShiftKey(byte *result, byte *src, int n, bool direction)
{
	int Length = 128;
	for (int i = 0; i < Length; i++)
		if (direction)
			result[(i + n)%Length] = src[i];
		else
			result[i] = src[(i + n)%Length];
}

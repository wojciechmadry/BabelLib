#ifndef TESTS_SHA_HPP
#define TESTS_SHA_HPP

#include "babel.hpp"
#include <vector>

namespace TESTING{
    void SHA_HASH_TEST() noexcept
    {
        std::vector<std::string> SHA1 = {
                "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed",
                "667922d670dedc11b42f2559ab450464b7acb991",
                "efc0268c45856d09a2c8c555c0a9ba3aba414f73",
                "b965981445b816ec8430ad837fe4fb94a6676072",
                "8efd86fb78a56a5145ed7739dcb00c78581c5375",
                "da39a3ee5e6b4b0d3255bfef95601890afd80709",
                "1e5ae15c99b98ab45c89d87a159f361e974ac21e"
        };
        std::vector<std::string> SHA224 = {
                "2f05477fc24bb4faefd86517156dafdecec45b8ad3cf2522a563582b",
                "f84e9b896d9b90467727704a7d274dd5d2b58a8f450c25412e6e2815",
                "b00dc19d9ac2f00af60a68605d5a2bcb3518d103c75b7ba54bee914a",
                "c6627c8efd18bcac1da46f2fe29ada915628381a30ca33ae3ef8fef5",
                "8a27683839f9c2be2028e11d0e622fb152309c1c29392d44669c4154",
                "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f",
                "556f3db59bdb9ebb843967879c5ab41109e0863a0a4fce1ef2d40b06"
        };
        std::vector<std::string> SHA256 = {
                "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9",
                "5a1da66f7a404f517a39e474fab04a9cf38df2167f826e673ce759a760ad9501",
                "e16ae14d7186dd2565a8bf048818039cca6a003d501a83a2dbe2d90d0be147e3",
                "c19b220990b2f6e22b005446fc9c78c086041d06b75cbe476302d5f6cc9f06e3",
                "e3b98a4da31a127d4bde6e43033f66ba274cab0eb7eb1c70ec41402bf6273dd8",
                "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
                "8304f43e17bef742c28347684d6b713d404ea0251a5960ce9b520b774b4ac015"
        };
        std::vector<std::string> SHA384 = {
                "fdbd8e75a67f29f701a4e040385e2e23986303ea10239211af907fcbb83578b3e417cb71ce646efd0819dd8c088de1bd",
                "5472b6207632e03b124e2e2070db5c173b1c2d2187b39ac97fe20428297bfcf4f1c610fa6e0fce32789ef408bd22da61",
                "3ab37014cf9dbc295be4a1cd04e65e379fb52942c649ae81940cdbb389b3f8a689244a62d93b40d47832f52e15b52adf",
                "02fe725cc73b204b83a4b35b3281cd1d0a6e9a96c73f4d46e822fd990324ea61c358b595645b557bf39b960b4990fca4",
                "e7cdceeaff40fcf3eb07011b4facb47e6c06f82d243289ca9e598282f1e58ea4ee2378d5772c26e926ecbffba13f6d53",
                "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b",
                "7ffa20f03b8e110e6f0578c72cb697b282147eeaba17ffc8900ccc145115aa1c89994cc8206aabaca0b5ad480958b0c8"
        };
        std::vector<std::string> SHA512 = {
                "309ecc489c12d6eb4cc40f50c902f2b4d0ed77ee511a7c7a9bcd3ca86d4cd86f989dd35bc5ff499670da34255b45b0cfd830e81f605dcf7dc5542e93ae9cd76f",
                "c293bba14663b092d34a2a8610a4cdc1e11a6483bb55c6255ac5357a5c849e1b58ce3c0906100c641a6f184f9b1d45ab88a44be15e59239ccf2331425e493a66",
                "5a04eca1ef9b7a92843017ee49b421fc1381eb0ae2d3e72e73731c99fc0cc139b984551d12ea64374855e63f79cfb2d8e25e834441ba87179fcf8addbfc79933",
                "e38bd66bb3368458296ac3c9ecc5d634da032ca1f38926f193c7e66324ca3a45bc283916d3727b32581dc9b9e9a1fbc1e857eafb612b1d0ad713de09caa38211",
                "99f97d455d5d62b24f3a942a1abc3fa8863fc0ce2037f52f09bd785b22b800d4f2e7b2b614cb600ffc2a4fe24679845b24886d69bb776fcfa46e54d188889c6f",
                "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
                "24c140f70848fc37a5a9d96ec649bc0da524d0a96e5a915903745cb462b02cfd0be9f77050bc4450b9e0dd92a081c750fa5ed1b6584247594096bc2787ce76ba"
        };

        std::vector<std::string> SHA512_224 = {
                "22e0d52336f64a998085078b05a6e37b26f8120f43bf4db4c43a64ee",
                "0f4b7f5c8b81a5338ab38cdd23fe88e9ea9722b7216ea3e093f838e7",
                "aea4eaf76b3c88d8fc7523de2fb1cb0697c236e6a886dd66d163858f",
                "57dbe76c65925a7ef7c8ef1d00f3b88b39aa214ede7254e0e1d82143",
                "4577aa10739fb44cbabf18b46117804ddeac21c40b9462844f071523",
                "6ed0dd02806fa89e25de060c19d3ac86cabb87d6a0ddd05c333b84f4",
                "dbb893f21b6c41b6180356b6e37b66a9bbd218d3849b5ac65880fa58"
        };

        std::vector<std::string> SHA512_256 = {
                "0ac561fac838104e3f2e4ad107b4bee3e938bf15f2b15f009ccccd61a913f017",
                "c0ed197119e31ab545a395c1bd2eb01207a78cbc885ca0b603b8be66f8e952cc",
                "0df7265e8b48c6b436d887dc4b9990c183e674ee8ccdb13080149da87a27aa0a",
                "33ad829b2c7c2c8489a07294bf7c4c0747bfc81e20f9b8994e1b2d2f069e6bb1",
                "91c9cb62865a010e804e1ebc896a753939decc6a0baaf00951e79aa9f2ad8c87",
                "c672b8d1ef56ed28ab87c3622c5114069bdd3ad7b8f9737498d0c01ecef0967a",
                "b3c056a85d2b20832c77c0dae15016d972f2b8eca74aa23332456656c38248a9"
        };

        std::vector<std::string> msg = {
                "hello world",
                "hello world,hello world,hello world",
                "hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world",
                "asgasmngmxczmvmxz mcxz kasf asf as",
                "t",
                "",
                "TESTED STRING"
        };
        for ( std::size_t i = 0 ; i < msg.size() ; ++i )
        {
            assert (babel::ALGO::CRYPT::sha1(msg[i]) == SHA1[i]);
            assert (babel::ALGO::CRYPT::sha224(msg[i]) == SHA224[i]);
            assert (babel::ALGO::CRYPT::sha256(msg[i]) == SHA256[i]);
            assert (babel::ALGO::CRYPT::sha384(msg[i]) == SHA384[i]);
            assert (babel::ALGO::CRYPT::sha512(msg[i]) == SHA512[i]);
            assert (babel::ALGO::CRYPT::sha512t<224>(msg[i]) == SHA512_224[i]);
            assert (babel::ALGO::CRYPT::sha512t<256>(msg[i]) == SHA512_256[i]);
        }
    }

}

#endif  // TESTS_SHA_HPP

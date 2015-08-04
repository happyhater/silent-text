LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
LOCAL_MODULE   := sccrypto
LOCAL_CFLAGS   := -DANDROID
LOCAL_LDLIBS   := -llog
LOCAL_CFLAGS += -std=c99

LOCAL_C_INCLUDES := \
  $(LOCAL_PATH)/yajl \
  $(LOCAL_PATH)/tommath \
  $(LOCAL_PATH)/tomcrypt/hashes/skein \
  $(LOCAL_PATH)/tomcrypt/headers \
  $(LOCAL_PATH)/sccrypto \
  $(LOCAL_PATH)/scimp \
  $(LOCAL_PATH)/scloud

LOCAL_SRC_FILES := \
  sccrypto/SCccm.c \
  sccrypto/SCcrypto.c \
  sccrypto/SCkeys.c \
  sccrypto/SCutilities.c \
  sccrypto/SirenHash.c \
  tomcrypt/ciphers/aes/aes.c \
  tomcrypt/ciphers/twofish/twofish_tab.c \
  tomcrypt/ciphers/twofish/twofish.c \
  tomcrypt/encauth/ccm/ccm_memory_ex.c \
  tomcrypt/encauth/ccm/ccm_memory.c \
  tomcrypt/encauth/ccm/ccm_test.c \
  tomcrypt/encauth/gcm/gcm_add_aad.c \
  tomcrypt/encauth/gcm/gcm_add_iv.c \
  tomcrypt/encauth/gcm/gcm_done.c \
  tomcrypt/encauth/gcm/gcm_gf_mult.c \
  tomcrypt/encauth/gcm/gcm_init.c \
  tomcrypt/encauth/gcm/gcm_memory.c \
  tomcrypt/encauth/gcm/gcm_mult_h.c \
  tomcrypt/encauth/gcm/gcm_process.c \
  tomcrypt/encauth/gcm/gcm_reset.c \
  tomcrypt/encauth/gcm/gcm_test.c \
  tomcrypt/hashes/helper/hash_file.c \
  tomcrypt/hashes/helper/hash_filehandle.c \
  tomcrypt/hashes/helper/hash_memory.c \
  tomcrypt/hashes/md5.c \
  tomcrypt/hashes/sha1.c \
  tomcrypt/hashes/sha2/sha256.c \
  tomcrypt/hashes/sha2/sha512.c \
  tomcrypt/hashes/skein/skein_block.c \
  tomcrypt/hashes/skein/skein_tc.c \
  tomcrypt/hashes/skein/skein.c \
  tomcrypt/hashes/skein/skeinApi.c \
  tomcrypt/hashes/skein/threefish_tc.c \
  tomcrypt/hashes/skein/threefish1024Block.c \
  tomcrypt/hashes/skein/threefish256Block.c \
  tomcrypt/hashes/skein/threefish512Block.c \
  tomcrypt/hashes/skein/threefishApi.c \
  tomcrypt/mac/hmac/hmac_done.c \
  tomcrypt/mac/hmac/hmac_file.c \
  tomcrypt/mac/hmac/hmac_init.c \
  tomcrypt/mac/hmac/hmac_memory_multi.c \
  tomcrypt/mac/hmac/hmac_memory.c \
  tomcrypt/mac/hmac/hmac_process.c \
  tomcrypt/mac/hmac/hmac_test.c \
  tomcrypt/math/ltm_desc.c \
  tomcrypt/math/multi.c \
  tomcrypt/math/rand_prime.c \
  tomcrypt/misc/base64/base64_decode.c \
  tomcrypt/misc/base64/base64_encode.c \
  tomcrypt/misc/burn_stack.c \
  tomcrypt/misc/crypt/crypt_argchk.c \
  tomcrypt/misc/crypt/crypt_cipher_descriptor.c \
  tomcrypt/misc/crypt/crypt_cipher_is_valid.c \
  tomcrypt/misc/crypt/crypt_find_cipher_any.c \
  tomcrypt/misc/crypt/crypt_find_cipher_id.c \
  tomcrypt/misc/crypt/crypt_find_cipher.c \
  tomcrypt/misc/crypt/crypt_find_hash_any.c \
  tomcrypt/misc/crypt/crypt_find_hash_id.c \
  tomcrypt/misc/crypt/crypt_find_hash_oid.c \
  tomcrypt/misc/crypt/crypt_find_hash.c \
  tomcrypt/misc/crypt/crypt_find_prng.c \
  tomcrypt/misc/crypt/crypt_fsa.c \
  tomcrypt/misc/crypt/crypt_hash_descriptor.c \
  tomcrypt/misc/crypt/crypt_hash_is_valid.c \
  tomcrypt/misc/crypt/crypt_ltc_mp_descriptor.c \
  tomcrypt/misc/crypt/crypt_prng_descriptor.c \
  tomcrypt/misc/crypt/crypt_prng_is_valid.c \
  tomcrypt/misc/crypt/crypt_register_cipher.c \
  tomcrypt/misc/crypt/crypt_register_hash.c \
  tomcrypt/misc/crypt/crypt_register_prng.c \
  tomcrypt/misc/crypt/crypt_unregister_cipher.c \
  tomcrypt/misc/crypt/crypt_unregister_hash.c \
  tomcrypt/misc/crypt/crypt_unregister_prng.c \
  tomcrypt/misc/crypt/crypt.c \
  tomcrypt/misc/error_to_string.c \
  tomcrypt/misc/pk_get_oid.c \
  tomcrypt/misc/pkcs5/pkcs_5_2.c \
  tomcrypt/misc/zeromem.c \
  tomcrypt/modes/cbc/cbc_decrypt.c \
  tomcrypt/modes/cbc/cbc_done.c \
  tomcrypt/modes/cbc/cbc_encrypt.c \
  tomcrypt/modes/cbc/cbc_getiv.c \
  tomcrypt/modes/cbc/cbc_setiv.c \
  tomcrypt/modes/cbc/cbc_start.c \
  tomcrypt/modes/cfb/cfb_decrypt.c \
  tomcrypt/modes/cfb/cfb_done.c \
  tomcrypt/modes/cfb/cfb_encrypt.c \
  tomcrypt/modes/cfb/cfb_getiv.c \
  tomcrypt/modes/cfb/cfb_setiv.c \
  tomcrypt/modes/cfb/cfb_start.c \
  tomcrypt/modes/ctr/ctr_decrypt.c \
  tomcrypt/modes/ctr/ctr_done.c \
  tomcrypt/modes/ctr/ctr_encrypt.c \
  tomcrypt/modes/ctr/ctr_getiv.c \
  tomcrypt/modes/ctr/ctr_setiv.c \
  tomcrypt/modes/ctr/ctr_start.c \
  tomcrypt/modes/ctr/ctr_test.c \
  tomcrypt/modes/ecb/ecb_decrypt.c \
  tomcrypt/modes/ecb/ecb_done.c \
  tomcrypt/modes/ecb/ecb_encrypt.c \
  tomcrypt/modes/ecb/ecb_start.c \
  tomcrypt/pk/asn1/der/bit/der_decode_bit_string.c \
  tomcrypt/pk/asn1/der/bit/der_decode_raw_bit_string.c \
  tomcrypt/pk/asn1/der/bit/der_encode_bit_string.c \
  tomcrypt/pk/asn1/der/bit/der_encode_raw_bit_string.c \
  tomcrypt/pk/asn1/der/bit/der_length_bit_string.c \
  tomcrypt/pk/asn1/der/boolean/der_decode_boolean.c \
  tomcrypt/pk/asn1/der/boolean/der_encode_boolean.c \
  tomcrypt/pk/asn1/der/boolean/der_length_boolean.c \
  tomcrypt/pk/asn1/der/choice/der_decode_choice.c \
  tomcrypt/pk/asn1/der/ia5/der_decode_ia5_string.c \
  tomcrypt/pk/asn1/der/ia5/der_encode_ia5_string.c \
  tomcrypt/pk/asn1/der/ia5/der_length_ia5_string.c \
  tomcrypt/pk/asn1/der/integer/der_decode_integer.c \
  tomcrypt/pk/asn1/der/integer/der_encode_integer.c \
  tomcrypt/pk/asn1/der/integer/der_length_integer.c \
  tomcrypt/pk/asn1/der/object_identifier/der_decode_object_identifier.c \
  tomcrypt/pk/asn1/der/object_identifier/der_encode_object_identifier.c \
  tomcrypt/pk/asn1/der/object_identifier/der_length_object_identifier.c \
  tomcrypt/pk/asn1/der/octet/der_decode_octet_string.c \
  tomcrypt/pk/asn1/der/octet/der_encode_octet_string.c \
  tomcrypt/pk/asn1/der/octet/der_length_octet_string.c \
  tomcrypt/pk/asn1/der/printable_string/der_decode_printable_string.c \
  tomcrypt/pk/asn1/der/printable_string/der_encode_printable_string.c \
  tomcrypt/pk/asn1/der/printable_string/der_length_printable_string.c \
  tomcrypt/pk/asn1/der/sequence/der_decode_sequence_ex.c \
  tomcrypt/pk/asn1/der/sequence/der_decode_sequence_flexi.c \
  tomcrypt/pk/asn1/der/sequence/der_decode_sequence_multi.c \
  tomcrypt/pk/asn1/der/sequence/der_decode_subject_public_key_info.c \
  tomcrypt/pk/asn1/der/sequence/der_encode_sequence_ex.c \
  tomcrypt/pk/asn1/der/sequence/der_encode_sequence_multi.c \
  tomcrypt/pk/asn1/der/sequence/der_encode_subject_public_key_info.c \
  tomcrypt/pk/asn1/der/sequence/der_length_sequence.c \
  tomcrypt/pk/asn1/der/sequence/der_sequence_free.c \
  tomcrypt/pk/asn1/der/set/der_encode_set.c \
  tomcrypt/pk/asn1/der/set/der_encode_setof.c \
  tomcrypt/pk/asn1/der/short_integer/der_decode_short_integer.c \
  tomcrypt/pk/asn1/der/short_integer/der_encode_short_integer.c \
  tomcrypt/pk/asn1/der/short_integer/der_length_short_integer.c \
  tomcrypt/pk/asn1/der/utctime/der_decode_utctime.c \
  tomcrypt/pk/asn1/der/utctime/der_encode_utctime.c \
  tomcrypt/pk/asn1/der/utctime/der_length_utctime.c \
  tomcrypt/pk/asn1/der/utf8/der_decode_utf8_string.c \
  tomcrypt/pk/asn1/der/utf8/der_encode_utf8_string.c \
  tomcrypt/pk/asn1/der/utf8/der_length_utf8_string.c \
  tomcrypt/pk/dsa/dsa_decrypt_key.c \
  tomcrypt/pk/dsa/dsa_encrypt_key.c \
  tomcrypt/pk/dsa/dsa_export.c \
  tomcrypt/pk/dsa/dsa_free.c \
  tomcrypt/pk/dsa/dsa_import.c \
  tomcrypt/pk/dsa/dsa_make_key.c \
  tomcrypt/pk/dsa/dsa_shared_secret.c \
  tomcrypt/pk/dsa/dsa_sign_hash.c \
  tomcrypt/pk/dsa/dsa_verify_hash.c \
  tomcrypt/pk/dsa/dsa_verify_key.c \
  tomcrypt/pk/ecc_bl/ecc_bl_ansi_x963_import.c \
  tomcrypt/pk/ecc_bl/ecc_bl_decrypt_key.c \
  tomcrypt/pk/ecc_bl/ecc_bl_encrypt_key.c \
  tomcrypt/pk/ecc_bl/ecc_bl_import.c \
  tomcrypt/pk/ecc_bl/ecc_bl_make_key.c \
  tomcrypt/pk/ecc_bl/ecc_bl_sign_hash.c \
  tomcrypt/pk/ecc_bl/ecc_bl_verify_hash.c \
  tomcrypt/pk/ecc_bl/ecc_bl.c \
  tomcrypt/pk/ecc/ecc_ansi_x963_export.c \
  tomcrypt/pk/ecc/ecc_ansi_x963_import.c \
  tomcrypt/pk/ecc/ecc_decrypt_key.c \
  tomcrypt/pk/ecc/ecc_encrypt_key.c \
  tomcrypt/pk/ecc/ecc_export.c \
  tomcrypt/pk/ecc/ecc_free.c \
  tomcrypt/pk/ecc/ecc_get_size.c \
  tomcrypt/pk/ecc/ecc_import.c \
  tomcrypt/pk/ecc/ecc_make_key.c \
  tomcrypt/pk/ecc/ecc_shared_secret.c \
  tomcrypt/pk/ecc/ecc_sign_hash.c \
  tomcrypt/pk/ecc/ecc_sizes.c \
  tomcrypt/pk/ecc/ecc_test.c \
  tomcrypt/pk/ecc/ecc_verify_hash.c \
  tomcrypt/pk/ecc/ecc.c \
  tomcrypt/pk/ecc/ltc_ecc_is_valid_idx.c \
  tomcrypt/pk/ecc/ltc_ecc_map.c \
  tomcrypt/pk/ecc/ltc_ecc_mul2add.c \
  tomcrypt/pk/ecc/ltc_ecc_mulmod_timing.c \
  tomcrypt/pk/ecc/ltc_ecc_mulmod.c \
  tomcrypt/pk/ecc/ltc_ecc_points.c \
  tomcrypt/pk/ecc/ltc_ecc_projective_add_point.c \
  tomcrypt/pk/ecc/ltc_ecc_projective_dbl_point.c \
  tomcrypt/pk/pkcs1/pkcs_1_i2osp.c \
  tomcrypt/pk/pkcs1/pkcs_1_mgf1.c \
  tomcrypt/pk/pkcs1/pkcs_1_oaep_decode.c \
  tomcrypt/pk/pkcs1/pkcs_1_oaep_encode.c \
  tomcrypt/pk/pkcs1/pkcs_1_os2ip.c \
  tomcrypt/pk/pkcs1/pkcs_1_pss_decode.c \
  tomcrypt/pk/pkcs1/pkcs_1_pss_encode.c \
  tomcrypt/pk/pkcs1/pkcs_1_v1_5_decode.c \
  tomcrypt/pk/pkcs1/pkcs_1_v1_5_encode.c \
  tomcrypt/pk/rsa/rsa_decrypt_key.c \
  tomcrypt/pk/rsa/rsa_encrypt_key.c \
  tomcrypt/pk/rsa/rsa_export.c \
  tomcrypt/pk/rsa/rsa_exptmod.c \
  tomcrypt/pk/rsa/rsa_free.c \
  tomcrypt/pk/rsa/rsa_import.c \
  tomcrypt/pk/rsa/rsa_make_key.c \
  tomcrypt/pk/rsa/rsa_sign_hash.c \
  tomcrypt/pk/rsa/rsa_verify_hash.c \
  tomcrypt/prngs/rng_get_bytes.c \
  tomcrypt/prngs/rng_make_prng.c \
  tomcrypt/prngs/sprng.c \
  tomcrypt/prngs/yarrow.c \
  tommath/bn_error.c \
  tommath/bn_fast_mp_invmod.c \
  tommath/bn_fast_mp_montgomery_reduce.c \
  tommath/bn_fast_s_mp_mul_digs.c \
  tommath/bn_fast_s_mp_mul_high_digs.c \
  tommath/bn_fast_s_mp_sqr.c \
  tommath/bn_mp_2expt.c \
  tommath/bn_mp_abs.c \
  tommath/bn_mp_add_d.c \
  tommath/bn_mp_add.c \
  tommath/bn_mp_addmod.c \
  tommath/bn_mp_and.c \
  tommath/bn_mp_clamp.c \
  tommath/bn_mp_clear_multi.c \
  tommath/bn_mp_clear.c \
  tommath/bn_mp_cmp_d.c \
  tommath/bn_mp_cmp_mag.c \
  tommath/bn_mp_cmp.c \
  tommath/bn_mp_cnt_lsb.c \
  tommath/bn_mp_copy.c \
  tommath/bn_mp_count_bits.c \
  tommath/bn_mp_div_2.c \
  tommath/bn_mp_div_2d.c \
  tommath/bn_mp_div_3.c \
  tommath/bn_mp_div_d.c \
  tommath/bn_mp_div.c \
  tommath/bn_mp_dr_is_modulus.c \
  tommath/bn_mp_dr_reduce.c \
  tommath/bn_mp_dr_setup.c \
  tommath/bn_mp_exch.c \
  tommath/bn_mp_expt_d.c \
  tommath/bn_mp_exptmod_fast.c \
  tommath/bn_mp_exptmod.c \
  tommath/bn_mp_exteuclid.c \
  tommath/bn_mp_fread.c \
  tommath/bn_mp_fwrite.c \
  tommath/bn_mp_gcd.c \
  tommath/bn_mp_get_int.c \
  tommath/bn_mp_grow.c \
  tommath/bn_mp_init_copy.c \
  tommath/bn_mp_init_multi.c \
  tommath/bn_mp_init_set_int.c \
  tommath/bn_mp_init_set.c \
  tommath/bn_mp_init_size.c \
  tommath/bn_mp_init.c \
  tommath/bn_mp_invmod_slow.c \
  tommath/bn_mp_invmod.c \
  tommath/bn_mp_is_square.c \
  tommath/bn_mp_jacobi.c \
  tommath/bn_mp_karatsuba_mul.c \
  tommath/bn_mp_karatsuba_sqr.c \
  tommath/bn_mp_lcm.c \
  tommath/bn_mp_lshd.c \
  tommath/bn_mp_mod_2d.c \
  tommath/bn_mp_mod_d.c \
  tommath/bn_mp_mod.c \
  tommath/bn_mp_montgomery_calc_normalization.c \
  tommath/bn_mp_montgomery_reduce.c \
  tommath/bn_mp_montgomery_setup.c \
  tommath/bn_mp_mul_2.c \
  tommath/bn_mp_mul_2d.c \
  tommath/bn_mp_mul_d.c \
  tommath/bn_mp_mul.c \
  tommath/bn_mp_mulmod.c \
  tommath/bn_mp_n_root.c \
  tommath/bn_mp_neg.c \
  tommath/bn_mp_or.c \
  tommath/bn_mp_prime_fermat.c \
  tommath/bn_mp_prime_is_divisible.c \
  tommath/bn_mp_prime_is_prime.c \
  tommath/bn_mp_prime_miller_rabin.c \
  tommath/bn_mp_prime_next_prime.c \
  tommath/bn_mp_prime_rabin_miller_trials.c \
  tommath/bn_mp_prime_random_ex.c \
  tommath/bn_mp_radix_size.c \
  tommath/bn_mp_radix_smap.c \
  tommath/bn_mp_rand.c \
  tommath/bn_mp_read_radix.c \
  tommath/bn_mp_read_signed_bin.c \
  tommath/bn_mp_read_unsigned_bin.c \
  tommath/bn_mp_reduce_2k_l.c \
  tommath/bn_mp_reduce_2k_setup_l.c \
  tommath/bn_mp_reduce_2k_setup.c \
  tommath/bn_mp_reduce_2k.c \
  tommath/bn_mp_reduce_is_2k_l.c \
  tommath/bn_mp_reduce_is_2k.c \
  tommath/bn_mp_reduce_setup.c \
  tommath/bn_mp_reduce.c \
  tommath/bn_mp_rshd.c \
  tommath/bn_mp_set_int.c \
  tommath/bn_mp_set.c \
  tommath/bn_mp_shrink.c \
  tommath/bn_mp_signed_bin_size.c \
  tommath/bn_mp_sqr.c \
  tommath/bn_mp_sqrmod.c \
  tommath/bn_mp_sqrt.c \
  tommath/bn_mp_sub_d.c \
  tommath/bn_mp_sub.c \
  tommath/bn_mp_submod.c \
  tommath/bn_mp_to_signed_bin_n.c \
  tommath/bn_mp_to_signed_bin.c \
  tommath/bn_mp_to_unsigned_bin_n.c \
  tommath/bn_mp_to_unsigned_bin.c \
  tommath/bn_mp_toom_mul.c \
  tommath/bn_mp_toom_sqr.c \
  tommath/bn_mp_toradix_n.c \
  tommath/bn_mp_toradix.c \
  tommath/bn_mp_unsigned_bin_size.c \
  tommath/bn_mp_xor.c \
  tommath/bn_mp_zero.c \
  tommath/bn_prime_tab.c \
  tommath/bn_reverse.c \
  tommath/bn_s_mp_add.c \
  tommath/bn_s_mp_exptmod.c \
  tommath/bn_s_mp_mul_digs.c \
  tommath/bn_s_mp_mul_high_digs.c \
  tommath/bn_s_mp_sqr.c \
  tommath/bn_s_mp_sub.c \
  tommath/bncore.c \
  yajl/yajl_alloc.c \
  yajl/yajl_buf.c \
  yajl/yajl_encode.c \
  yajl/yajl_gen.c \
  yajl/yajl_lex.c \
  yajl/yajl_parser.c \
  yajl/yajl_tree.c \
  yajl/yajl_version.c \
  yajl/yajl.c \
  scloud/SCloud.c \
  scloud/SCloudJSON.c \
  scimp/SCimp.c \
  scimp/SCimpProtocol.c \
  scimp/SCimpProtocolFmtJSON.c

LOCAL_EXPORT_C_INCLUDES := \
  $(LOCAL_PATH)/sccrypto \
  $(LOCAL_PATH)/scimp \
  $(LOCAL_PATH)/scloud

include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/jni/Android.mk
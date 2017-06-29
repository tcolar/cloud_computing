# Security

## Basic concepts

Treats:
- Leakage (unauthorized access)
- Tampering (modification)
- Vandalism (interference, ie DDOS)

Common attacks:
- Eavesdropping
- Masquerading
- Tampering
- Replay attack

CIA properties:
- Conhidentiality (no leakage)
- Integrity (no tempering)
- Availability

Policies VS Mechanisms(impl)

Golden A's:
- Authentication
- Authorization
- Auditing

##  Basic Cryptography
Encryption - Key = secret seq of files to lock a msg


Symetric systems: 
- same key to encrypt and decrypt  (ie DES)

Public / Private key; ie : RSA, PGP
- Encrypted by private can only be decrypted by public
- Encrypted by public can only be decrypted by private

## Implementations

## Authentication
- Direct 
- Indirect (using a third party authentication server)

Direct authentication:
- Use nonce (random number)
- watch for replay attacks

Indirect:
- Ticket (oncrypted shared key)

## Digital signatures
- Authgentic, unforgeable
- Verifiable, non-repudiable

To sign, Alice encrypts a message with her private key

To be more efficient, hash the message first(fast) with say MD5 or SHA1 and encrypt that 

## Digital certificates
- Implemented with sigantures
- Transitive (chains)
- Can route back to the root authority

Sign based on a hash of user info (ie: name + account number)

## Authorization
- Access Control Matrix : Prinicpal(users) to object permissions mapping (large, sparse)
- Access control list : per object list of principal and rights
- Capability list: per principal list of objects and rights

 
 

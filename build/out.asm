Dump of assembler code for function gaussianiir2d:
../src/cg_image.h:
189	{
   0x000000000043e260 <+0>:	push   rbp
   0x000000000043e261 <+1>:	push   r15
   0x000000000043e263 <+3>:	push   r14
   0x000000000043e265 <+5>:	push   r13
   0x000000000043e267 <+7>:	push   r12
   0x000000000043e269 <+9>:	push   rbx
   0x000000000043e26a <+10>:	sub    rsp,0x38
   0x000000000043e26e <+14>:	mov    r15d,ecx
   0x000000000043e271 <+17>:	mov    rbp,rdx
   0x000000000043e274 <+20>:	mov    QWORD PTR [rsp+0x28],rbp
   0x000000000043e279 <+25>:	mov    rbx,rsi

194	    size_t i, x, y;
195	    int step;
196	
197	    if(sigma <= 0 || numsteps < 0)
   0x000000000043e27c <+28>:	xorps  xmm1,xmm1
   0x000000000043e27f <+31>:	ucomiss xmm1,xmm0
   0x000000000043e282 <+34>:	jae    0x43eab5 <gaussianiir2d+2133>
   0x000000000043e288 <+40>:	test   r15d,r15d
   0x000000000043e28b <+43>:	js     0x43eab5 <gaussianiir2d+2133>
   0x000000000043e291 <+49>:	mov    QWORD PTR [rsp+0x8],rdi

198	        return;
199	
200	    lambda = (sigma*sigma)/(2.0*numsteps);
   0x000000000043e296 <+54>:	mulss  xmm0,xmm0
   0x000000000043e29a <+58>:	cvtss2sd xmm2,xmm0
   0x000000000043e29e <+62>:	xorps  xmm0,xmm0
   0x000000000043e2a1 <+65>:	cvtsi2sd xmm0,r15d
   0x000000000043e2a6 <+70>:	addsd  xmm0,xmm0
   0x000000000043e2aa <+74>:	divsd  xmm2,xmm0

201	    dnu = (1.0 + 2.0*lambda - sqrt(1.0 + 4.0*lambda))/(2.0*lambda);
   0x000000000043e2ae <+78>:	movapd xmm5,xmm2
   0x000000000043e2b2 <+82>:	addsd  xmm5,xmm5
   0x000000000043e2b6 <+86>:	movsd  xmm4,QWORD PTR [rip+0x21e72]        # 0x460130
   0x000000000043e2be <+94>:	movapd xmm3,xmm5
   0x000000000043e2c2 <+98>:	addsd  xmm3,xmm4
   0x000000000043e2c6 <+102>:	movsd  xmm0,QWORD PTR [rip+0x21eba]        # 0x460188
   0x000000000043e2ce <+110>:	mulsd  xmm0,xmm2
   0x000000000043e2d2 <+114>:	addsd  xmm0,xmm4
   0x000000000043e2d6 <+118>:	sqrtsd xmm1,xmm0
   0x000000000043e2da <+122>:	ucomisd xmm1,xmm1
   0x000000000043e2de <+126>:	jnp    0x43e315 <gaussianiir2d+181>
   0x000000000043e2e0 <+128>:	movsd  QWORD PTR [rsp+0x30],xmm2
   0x000000000043e2e6 <+134>:	movsd  QWORD PTR [rsp+0x20],xmm3
   0x000000000043e2ec <+140>:	movsd  QWORD PTR [rsp+0x18],xmm5
   0x000000000043e2f2 <+146>:	call   0x4020f0 <sqrt@plt>
   0x000000000043e2f7 <+151>:	movsd  xmm5,QWORD PTR [rsp+0x18]
   0x000000000043e2fd <+157>:	movsd  xmm4,QWORD PTR [rip+0x21e2b]        # 0x460130
   0x000000000043e305 <+165>:	movsd  xmm3,QWORD PTR [rsp+0x20]
   0x000000000043e30b <+171>:	movsd  xmm2,QWORD PTR [rsp+0x30]
   0x000000000043e311 <+177>:	movapd xmm1,xmm0
   0x000000000043e315 <+181>:	subsd  xmm3,xmm1
   0x000000000043e319 <+185>:	divsd  xmm3,xmm5

202	    nu = (float)dnu;
   0x000000000043e31d <+189>:	xorps  xmm0,xmm0
   0x000000000043e320 <+192>:	cvtsd2ss xmm0,xmm3

203	    boundaryscale = (float)(1.0/(1.0 - dnu));
   0x000000000043e324 <+196>:	movss  DWORD PTR [rsp+0x20],xmm0
   0x000000000043e32a <+202>:	movapd xmm0,xmm4
   0x000000000043e32e <+206>:	subsd  xmm0,xmm3
   0x000000000043e332 <+210>:	divsd  xmm4,xmm0
   0x000000000043e336 <+214>:	xorps  xmm0,xmm0
   0x000000000043e339 <+217>:	cvtsd2ss xmm0,xmm4

204	    postscale = (float)(pow(dnu/lambda,2*numsteps));
   0x000000000043e33d <+221>:	movss  DWORD PTR [rsp+0x18],xmm0
   0x000000000043e343 <+227>:	divsd  xmm3,xmm2
   0x000000000043e347 <+231>:	lea    eax,[r15+r15*1]
   0x000000000043e34b <+235>:	xorps  xmm1,xmm1
   0x000000000043e34e <+238>:	cvtsi2sd xmm1,eax
   0x000000000043e352 <+242>:	movapd xmm0,xmm3
   0x000000000043e356 <+246>:	call   0x402150 <pow@plt>

205	
206	    /* Filter horizontally along each row */
207	    for(y = 0; y < height; y++)
   0x000000000043e35b <+251>:	test   rbp,rbp
   0x000000000043e35e <+254>:	je     0x43e76f <gaussianiir2d+1295>

217	
218	            ptr[x = width - 1] *= boundaryscale;
   0x000000000043e364 <+260>:	lea    r13,[rbx-0x1]

207	    for(y = 0; y < height; y++)
   0x000000000043e368 <+264>:	lea    r14,[rbx-0x2]

213	
214	            /* Filter rightwards */
215	            for(x = 1; x < width; x++)
   0x000000000043e36c <+268>:	mov    edx,r13d
   0x000000000043e36f <+271>:	and    edx,0x3

193	    float *ptr;
   0x000000000043e372 <+274>:	mov    eax,r15d
   0x000000000043e375 <+277>:	and    eax,0x1
   0x000000000043e378 <+280>:	mov    DWORD PTR [rsp+0x4],eax
   0x000000000043e37c <+284>:	mov    rax,QWORD PTR [rsp+0x8]

205	
206	    /* Filter horizontally along each row */
207	    for(y = 0; y < height; y++)
   0x000000000043e381 <+289>:	lea    r10,[rax+rbx*4-0x8]
   0x000000000043e386 <+294>:	lea    rcx,[rbx*4+0x0]
   0x000000000043e38e <+302>:	mov    QWORD PTR [rsp+0x10],rcx
   0x000000000043e393 <+307>:	mov    r11,rdx
   0x000000000043e396 <+310>:	neg    r11
   0x000000000043e399 <+313>:	lea    rdi,[rax-0x8]
   0x000000000043e39d <+317>:	lea    r9,[rax+0x4]
   0x000000000043e3a1 <+321>:	lea    rax,[rax+0x8]
   0x000000000043e3a5 <+325>:	xor    ecx,ecx
   0x000000000043e3a7 <+327>:	mov    QWORD PTR [rsp+0x30],rcx
   0x000000000043e3ac <+332>:	movss  xmm2,DWORD PTR [rsp+0x20]
   0x000000000043e3b2 <+338>:	movss  xmm3,DWORD PTR [rsp+0x18]
   0x000000000043e3b8 <+344>:	nop    DWORD PTR [rax+rax*1+0x0]

208	    {
209	        for(step = 0; step < numsteps; step++)
   0x000000000043e3c0 <+352>:	test   r15d,r15d
   0x000000000043e3c3 <+355>:	jle    0x43e740 <gaussianiir2d+1248>

210	        {
211	            ptr = image + width*y;
   0x000000000043e3c9 <+361>:	mov    rcx,QWORD PTR [rsp+0x30]
   0x000000000043e3ce <+366>:	imul   rcx,rbx
   0x000000000043e3d2 <+370>:	mov    rsi,QWORD PTR [rsp+0x8]
   0x000000000043e3d7 <+375>:	lea    r8,[rsi+rcx*4]
   0x000000000043e3db <+379>:	xor    r12d,r12d

213	
214	            /* Filter rightwards */
215	            for(x = 1; x < width; x++)
   0x000000000043e3de <+382>:	cmp    rbx,0x2
   0x000000000043e3e2 <+386>:	jb     0x43e5f0 <gaussianiir2d+912>

219	
220	            /* Filter leftwards */
221	            for(; x > 0; x--)
   0x000000000043e3e8 <+392>:	test   r13,r13
   0x000000000043e3eb <+395>:	je     0x43e530 <gaussianiir2d+720>
   0x000000000043e3f1 <+401>:	data16 data16 data16 data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e400 <+416>:	test   rdx,rdx
   0x000000000043e403 <+419>:	movss  xmm1,DWORD PTR [r8]

212	            ptr[0] *= boundaryscale;
   0x000000000043e408 <+424>:	mulss  xmm1,xmm3
   0x000000000043e40c <+428>:	movss  DWORD PTR [r8],xmm1

216	                ptr[x] += nu*ptr[x - 1];
   0x000000000043e411 <+433>:	mov    rcx,r9
   0x000000000043e414 <+436>:	mov    ebp,0x0
   0x000000000043e419 <+441>:	mov    esi,0x1
   0x000000000043e41e <+446>:	je     0x43e440 <gaussianiir2d+480>
   0x000000000043e420 <+448>:	mov    rsi,rbp
   0x000000000043e423 <+451>:	mulss  xmm1,xmm2
   0x000000000043e427 <+455>:	addss  xmm1,DWORD PTR [rcx]
   0x000000000043e42b <+459>:	movss  DWORD PTR [rcx],xmm1

215	            for(x = 1; x < width; x++)
   0x000000000043e42f <+463>:	lea    rbp,[rsi+0x1]
   0x000000000043e433 <+467>:	add    rcx,0x4
   0x000000000043e437 <+471>:	cmp    rdx,rbp
   0x000000000043e43a <+474>:	jne    0x43e420 <gaussianiir2d+448>
   0x000000000043e43c <+476>:	add    rsi,0x2
   0x000000000043e440 <+480>:	cmp    r14,0x3
   0x000000000043e444 <+484>:	jb     0x43e492 <gaussianiir2d+562>
   0x000000000043e446 <+486>:	mov    rcx,rbx
   0x000000000043e449 <+489>:	sub    rcx,rsi
   0x000000000043e44c <+492>:	lea    rbp,[rax+rsi*4]

216	                ptr[x] += nu*ptr[x - 1];
   0x000000000043e450 <+496>:	mulss  xmm1,xmm2
   0x000000000043e454 <+500>:	addss  xmm1,DWORD PTR [rbp-0x8]
   0x000000000043e459 <+505>:	movss  DWORD PTR [rbp-0x8],xmm1
   0x000000000043e45e <+510>:	mulss  xmm1,xmm2
   0x000000000043e462 <+514>:	addss  xmm1,DWORD PTR [rbp-0x4]
   0x000000000043e467 <+519>:	movss  DWORD PTR [rbp-0x4],xmm1
   0x000000000043e46c <+524>:	mulss  xmm1,xmm2
   0x000000000043e470 <+528>:	addss  xmm1,DWORD PTR [rbp+0x0]
   0x000000000043e475 <+533>:	movss  DWORD PTR [rbp+0x0],xmm1
   0x000000000043e47a <+538>:	mulss  xmm1,xmm2
   0x000000000043e47e <+542>:	addss  xmm1,DWORD PTR [rbp+0x4]
   0x000000000043e483 <+547>:	movss  DWORD PTR [rbp+0x4],xmm1

215	            for(x = 1; x < width; x++)
   0x000000000043e488 <+552>:	add    rbp,0x10
   0x000000000043e48c <+556>:	add    rcx,0xfffffffffffffffc
   0x000000000043e490 <+560>:	jne    0x43e450 <gaussianiir2d+496>
   0x000000000043e492 <+562>:	test   rdx,rdx
   0x000000000043e495 <+565>:	movss  xmm1,DWORD PTR [r8+rbx*4-0x4]

217	
218	            ptr[x = width - 1] *= boundaryscale;
   0x000000000043e49c <+572>:	mulss  xmm1,xmm3
   0x000000000043e4a0 <+576>:	movss  DWORD PTR [r8+rbx*4-0x4],xmm1

222	                ptr[x - 1] += nu*ptr[x];
   0x000000000043e4a7 <+583>:	mov    rsi,r11
   0x000000000043e4aa <+586>:	mov    rcx,r13
   0x000000000043e4ad <+589>:	je     0x43e4c8 <gaussianiir2d+616>
   0x000000000043e4af <+591>:	nop
   0x000000000043e4b0 <+592>:	mulss  xmm1,xmm2
   0x000000000043e4b4 <+596>:	addss  xmm1,DWORD PTR [rdi+rcx*4+0x4]
   0x000000000043e4ba <+602>:	movss  DWORD PTR [rdi+rcx*4+0x4],xmm1
   0x000000000043e4c0 <+608>:	dec    rcx

221	            for(; x > 0; x--)
   0x000000000043e4c3 <+611>:	inc    rsi
   0x000000000043e4c6 <+614>:	jne    0x43e4b0 <gaussianiir2d+592>
   0x000000000043e4c8 <+616>:	cmp    r14,0x2
   0x000000000043e4cc <+620>:	jbe    0x43e514 <gaussianiir2d+692>
   0x000000000043e4ce <+622>:	xchg   ax,ax

222	                ptr[x - 1] += nu*ptr[x];
   0x000000000043e4d0 <+624>:	mulss  xmm1,xmm2
   0x000000000043e4d4 <+628>:	addss  xmm1,DWORD PTR [rdi+rcx*4+0x4]
   0x000000000043e4da <+634>:	movss  DWORD PTR [rdi+rcx*4+0x4],xmm1
   0x000000000043e4e0 <+640>:	mulss  xmm1,xmm2
   0x000000000043e4e4 <+644>:	addss  xmm1,DWORD PTR [rdi+rcx*4]
   0x000000000043e4e9 <+649>:	movss  DWORD PTR [rdi+rcx*4],xmm1
   0x000000000043e4ee <+654>:	mulss  xmm1,xmm2
   0x000000000043e4f2 <+658>:	addss  xmm1,DWORD PTR [rdi+rcx*4-0x4]
   0x000000000043e4f8 <+664>:	movss  DWORD PTR [rdi+rcx*4-0x4],xmm1
   0x000000000043e4fe <+670>:	mulss  xmm1,xmm2
   0x000000000043e502 <+674>:	addss  xmm1,DWORD PTR [rdi+rcx*4-0x8]
   0x000000000043e508 <+680>:	movss  DWORD PTR [rdi+rcx*4-0x8],xmm1

221	            for(; x > 0; x--)
   0x000000000043e50e <+686>:	add    rcx,0xfffffffffffffffc
   0x000000000043e512 <+690>:	jne    0x43e4d0 <gaussianiir2d+624>

209	        for(step = 0; step < numsteps; step++)
   0x000000000043e514 <+692>:	inc    r12d
   0x000000000043e517 <+695>:	cmp    r12d,r15d
   0x000000000043e51a <+698>:	jne    0x43e400 <gaussianiir2d+416>
   0x000000000043e520 <+704>:	jmp    0x43e740 <gaussianiir2d+1248>
   0x000000000043e525 <+709>:	data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e530 <+720>:	test   rdx,rdx
   0x000000000043e533 <+723>:	movss  xmm1,DWORD PTR [r8]

212	            ptr[0] *= boundaryscale;
   0x000000000043e538 <+728>:	mulss  xmm1,xmm3
   0x000000000043e53c <+732>:	movss  DWORD PTR [r8],xmm1
   0x000000000043e541 <+737>:	mov    esi,0x0
   0x000000000043e546 <+742>:	mov    ecx,0x1
   0x000000000043e54b <+747>:	je     0x43e570 <gaussianiir2d+784>
   0x000000000043e54d <+749>:	nop    DWORD PTR [rax]

216	                ptr[x] += nu*ptr[x - 1];
   0x000000000043e550 <+752>:	mov    rcx,rsi
   0x000000000043e553 <+755>:	mulss  xmm1,xmm2
   0x000000000043e557 <+759>:	addss  xmm1,DWORD PTR [r9+rcx*4]
   0x000000000043e55d <+765>:	movss  DWORD PTR [r9+rcx*4],xmm1

215	            for(x = 1; x < width; x++)
   0x000000000043e563 <+771>:	lea    rsi,[rcx+0x1]
   0x000000000043e567 <+775>:	cmp    rdx,rsi
   0x000000000043e56a <+778>:	jne    0x43e550 <gaussianiir2d+752>
   0x000000000043e56c <+780>:	add    rcx,0x2
   0x000000000043e570 <+784>:	cmp    r14,0x2
   0x000000000043e574 <+788>:	jbe    0x43e5c7 <gaussianiir2d+871>
   0x000000000043e576 <+790>:	nop    WORD PTR cs:[rax+rax*1+0x0]

216	                ptr[x] += nu*ptr[x - 1];
   0x000000000043e580 <+800>:	mulss  xmm1,xmm2
   0x000000000043e584 <+804>:	addss  xmm1,DWORD PTR [rax+rcx*4-0x8]
   0x000000000043e58a <+810>:	movss  DWORD PTR [rax+rcx*4-0x8],xmm1
   0x000000000043e590 <+816>:	mulss  xmm1,xmm2
   0x000000000043e594 <+820>:	addss  xmm1,DWORD PTR [rax+rcx*4-0x4]
   0x000000000043e59a <+826>:	movss  DWORD PTR [rax+rcx*4-0x4],xmm1
   0x000000000043e5a0 <+832>:	mulss  xmm1,xmm2
   0x000000000043e5a4 <+836>:	addss  xmm1,DWORD PTR [rax+rcx*4]
   0x000000000043e5a9 <+841>:	movss  DWORD PTR [rax+rcx*4],xmm1
   0x000000000043e5ae <+846>:	mulss  xmm1,xmm2
   0x000000000043e5b2 <+850>:	addss  xmm1,DWORD PTR [rax+rcx*4+0x4]
   0x000000000043e5b8 <+856>:	movss  DWORD PTR [rax+rcx*4+0x4],xmm1

215	            for(x = 1; x < width; x++)
   0x000000000043e5be <+862>:	add    rcx,0x4
   0x000000000043e5c2 <+866>:	cmp    rbx,rcx
   0x000000000043e5c5 <+869>:	jne    0x43e580 <gaussianiir2d+800>
   0x000000000043e5c7 <+871>:	movss  xmm1,DWORD PTR [r8+rbx*4-0x4]

217	
218	            ptr[x = width - 1] *= boundaryscale;
   0x000000000043e5ce <+878>:	mulss  xmm1,xmm3
   0x000000000043e5d2 <+882>:	movss  DWORD PTR [r8+rbx*4-0x4],xmm1

209	        for(step = 0; step < numsteps; step++)
   0x000000000043e5d9 <+889>:	inc    r12d
   0x000000000043e5dc <+892>:	cmp    r12d,r15d
   0x000000000043e5df <+895>:	jne    0x43e530 <gaussianiir2d+720>
   0x000000000043e5e5 <+901>:	jmp    0x43e740 <gaussianiir2d+1248>
   0x000000000043e5ea <+906>:	nop    WORD PTR [rax+rax*1+0x0]

219	
220	            /* Filter leftwards */
221	            for(; x > 0; x--)
   0x000000000043e5f0 <+912>:	test   r13,r13
   0x000000000043e5f3 <+915>:	je     0x43e6b1 <gaussianiir2d+1105>
   0x000000000043e5f9 <+921>:	nop    DWORD PTR [rax+0x0]
   0x000000000043e600 <+928>:	test   rdx,rdx
   0x000000000043e603 <+931>:	movss  xmm1,DWORD PTR [r8]

212	            ptr[0] *= boundaryscale;
   0x000000000043e608 <+936>:	mulss  xmm1,xmm3
   0x000000000043e60c <+940>:	movss  DWORD PTR [r8],xmm1
   0x000000000043e611 <+945>:	movss  xmm1,DWORD PTR [r8+rbx*4-0x4]

217	
218	            ptr[x = width - 1] *= boundaryscale;
   0x000000000043e618 <+952>:	mulss  xmm1,xmm3
   0x000000000043e61c <+956>:	movss  DWORD PTR [r8+rbx*4-0x4],xmm1

222	                ptr[x - 1] += nu*ptr[x];
   0x000000000043e623 <+963>:	mov    rsi,r11
   0x000000000043e626 <+966>:	mov    rbp,r10
   0x000000000043e629 <+969>:	mov    rcx,r13
   0x000000000043e62c <+972>:	je     0x43e64a <gaussianiir2d+1002>
   0x000000000043e62e <+974>:	xchg   ax,ax
   0x000000000043e630 <+976>:	mulss  xmm1,xmm2
   0x000000000043e634 <+980>:	dec    rcx
   0x000000000043e637 <+983>:	addss  xmm1,DWORD PTR [rbp+0x0]
   0x000000000043e63c <+988>:	movss  DWORD PTR [rbp+0x0],xmm1

221	            for(; x > 0; x--)
   0x000000000043e641 <+993>:	add    rbp,0xfffffffffffffffc
   0x000000000043e645 <+997>:	inc    rsi
   0x000000000043e648 <+1000>:	jne    0x43e630 <gaussianiir2d+976>
   0x000000000043e64a <+1002>:	cmp    r14,0x3
   0x000000000043e64e <+1006>:	jb     0x43e6a0 <gaussianiir2d+1088>
   0x000000000043e650 <+1008>:	lea    rsi,[rdi+rcx*4]
   0x000000000043e654 <+1012>:	data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]

222	                ptr[x - 1] += nu*ptr[x];
   0x000000000043e660 <+1024>:	mulss  xmm1,xmm2
   0x000000000043e664 <+1028>:	addss  xmm1,DWORD PTR [rsi+0x4]
   0x000000000043e669 <+1033>:	movss  DWORD PTR [rsi+0x4],xmm1
   0x000000000043e66e <+1038>:	mulss  xmm1,xmm2
   0x000000000043e672 <+1042>:	addss  xmm1,DWORD PTR [rsi]
   0x000000000043e676 <+1046>:	movss  DWORD PTR [rsi],xmm1
   0x000000000043e67a <+1050>:	mulss  xmm1,xmm2
   0x000000000043e67e <+1054>:	addss  xmm1,DWORD PTR [rsi-0x4]
   0x000000000043e683 <+1059>:	movss  DWORD PTR [rsi-0x4],xmm1
   0x000000000043e688 <+1064>:	mulss  xmm1,xmm2

221	            for(; x > 0; x--)
   0x000000000043e68c <+1068>:	add    rcx,0xfffffffffffffffc

222	                ptr[x - 1] += nu*ptr[x];
   0x000000000043e690 <+1072>:	addss  xmm1,DWORD PTR [rsi-0x8]
   0x000000000043e695 <+1077>:	movss  DWORD PTR [rsi-0x8],xmm1

221	            for(; x > 0; x--)
   0x000000000043e69a <+1082>:	lea    rsi,[rsi-0x10]
   0x000000000043e69e <+1086>:	jne    0x43e660 <gaussianiir2d+1024>

209	        for(step = 0; step < numsteps; step++)
   0x000000000043e6a0 <+1088>:	inc    r12d
   0x000000000043e6a3 <+1091>:	cmp    r12d,r15d
   0x000000000043e6a6 <+1094>:	jne    0x43e600 <gaussianiir2d+928>
   0x000000000043e6ac <+1100>:	jmp    0x43e740 <gaussianiir2d+1248>
   0x000000000043e6b1 <+1105>:	xor    esi,esi
   0x000000000043e6b3 <+1107>:	cmp    DWORD PTR [rsp+0x4],0x0
   0x000000000043e6b8 <+1112>:	je     0x43e6df <gaussianiir2d+1151>
   0x000000000043e6ba <+1114>:	movss  xmm1,DWORD PTR [r8]

212	            ptr[0] *= boundaryscale;
   0x000000000043e6bf <+1119>:	mulss  xmm1,xmm3
   0x000000000043e6c3 <+1123>:	movss  DWORD PTR [r8],xmm1
   0x000000000043e6c8 <+1128>:	movss  xmm1,DWORD PTR [r8+rbx*4-0x4]

217	
218	            ptr[x = width - 1] *= boundaryscale;
   0x000000000043e6cf <+1135>:	mulss  xmm1,xmm3
   0x000000000043e6d3 <+1139>:	movss  DWORD PTR [r8+rbx*4-0x4],xmm1
   0x000000000043e6da <+1146>:	mov    esi,0x1
   0x000000000043e6df <+1151>:	cmp    r15d,0x1
   0x000000000043e6e3 <+1155>:	je     0x43e740 <gaussianiir2d+1248>

193	    float *ptr;
   0x000000000043e6e5 <+1157>:	mov    ecx,r15d
   0x000000000043e6e8 <+1160>:	sub    ecx,esi
   0x000000000043e6ea <+1162>:	nop    WORD PTR [rax+rax*1+0x0]
   0x000000000043e6f0 <+1168>:	movss  xmm1,DWORD PTR [r8]

212	            ptr[0] *= boundaryscale;
   0x000000000043e6f5 <+1173>:	mulss  xmm1,xmm3
   0x000000000043e6f9 <+1177>:	movss  DWORD PTR [r8],xmm1
   0x000000000043e6fe <+1182>:	movss  xmm1,DWORD PTR [r8+rbx*4-0x4]

217	
218	            ptr[x = width - 1] *= boundaryscale;
   0x000000000043e705 <+1189>:	mulss  xmm1,xmm3
   0x000000000043e709 <+1193>:	movss  DWORD PTR [r8+rbx*4-0x4],xmm1
   0x000000000043e710 <+1200>:	movss  xmm1,DWORD PTR [r8]

212	            ptr[0] *= boundaryscale;
   0x000000000043e715 <+1205>:	mulss  xmm1,xmm3
   0x000000000043e719 <+1209>:	movss  DWORD PTR [r8],xmm1
   0x000000000043e71e <+1214>:	movss  xmm1,DWORD PTR [r8+rbx*4-0x4]

217	
218	            ptr[x = width - 1] *= boundaryscale;
   0x000000000043e725 <+1221>:	mulss  xmm1,xmm3
   0x000000000043e729 <+1225>:	movss  DWORD PTR [r8+rbx*4-0x4],xmm1

209	        for(step = 0; step < numsteps; step++)
   0x000000000043e730 <+1232>:	add    ecx,0xfffffffe
   0x000000000043e733 <+1235>:	jne    0x43e6f0 <gaussianiir2d+1168>
   0x000000000043e735 <+1237>:	data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e740 <+1248>:	mov    rcx,QWORD PTR [rsp+0x30]
   0x000000000043e745 <+1253>:	mov    rsi,rcx

207	    for(y = 0; y < height; y++)
   0x000000000043e748 <+1256>:	inc    rsi
   0x000000000043e74b <+1259>:	mov    QWORD PTR [rsp+0x30],rsi
   0x000000000043e750 <+1264>:	mov    rcx,QWORD PTR [rsp+0x10]
   0x000000000043e755 <+1269>:	add    r10,rcx
   0x000000000043e758 <+1272>:	add    rdi,rcx
   0x000000000043e75b <+1275>:	add    r9,rcx
   0x000000000043e75e <+1278>:	add    rax,rcx
   0x000000000043e761 <+1281>:	mov    rbp,QWORD PTR [rsp+0x28]
   0x000000000043e766 <+1286>:	cmp    rsi,rbp
   0x000000000043e769 <+1289>:	jne    0x43e3c0 <gaussianiir2d+352>

190	    const size_t numpixels = width*height;
   0x000000000043e76f <+1295>:	mov    r12,rbp
   0x000000000043e772 <+1298>:	imul   r12,rbx

223	        }
224	    }
225	
226	    /* Filter vertically along each column */
227	    for(x = 0; x < width; x++)
   0x000000000043e776 <+1302>:	test   rbx,rbx
   0x000000000043e779 <+1305>:	mov    r13,QWORD PTR [rsp+0x8]
   0x000000000043e77e <+1310>:	movss  xmm2,DWORD PTR [rsp+0x20]
   0x000000000043e784 <+1316>:	movss  xmm3,DWORD PTR [rsp+0x18]
   0x000000000043e78a <+1322>:	je     0x43e9d0 <gaussianiir2d+1904>

237	
238	            ptr[i = numpixels - width] *= boundaryscale;
   0x000000000043e790 <+1328>:	mov    r11,r12
   0x000000000043e793 <+1331>:	sub    r11,rbx

193	    float *ptr;
   0x000000000043e796 <+1334>:	mov    r8d,r15d
   0x000000000043e799 <+1337>:	and    r8d,0x1

223	        }
224	    }
225	
226	    /* Filter vertically along each column */
227	    for(x = 0; x < width; x++)
   0x000000000043e79d <+1341>:	mov    r9d,0x1
   0x000000000043e7a3 <+1347>:	sub    r9,rbp
   0x000000000043e7a6 <+1350>:	imul   r9,rbx
   0x000000000043e7aa <+1354>:	add    rbp,0xfffffffffffffffe
   0x000000000043e7ae <+1358>:	imul   rbp,rbx
   0x000000000043e7b2 <+1362>:	lea    r10,[r13+rbp*4+0x0]
   0x000000000043e7b7 <+1367>:	lea    rdx,[rbx*4+0x0]
   0x000000000043e7bf <+1375>:	mov    rbp,rdx
   0x000000000043e7c2 <+1378>:	neg    rbp
   0x000000000043e7c5 <+1381>:	xor    esi,esi
   0x000000000043e7c7 <+1383>:	nop    WORD PTR [rax+rax*1+0x0]

228	    {
229	        for(step = 0; step < numsteps; step++)
   0x000000000043e7d0 <+1392>:	test   r15d,r15d
   0x000000000043e7d3 <+1395>:	jle    0x43e9c0 <gaussianiir2d+1888>

230	        {
231	            ptr = image + x;
   0x000000000043e7d9 <+1401>:	lea    r14,[r13+rsi*4+0x0]
   0x000000000043e7de <+1406>:	xor    ecx,ecx

233	
234	            /* Filter downwards */
235	            for(i = width; i < numpixels; i += width)
   0x000000000043e7e0 <+1408>:	cmp    r12,rbx
   0x000000000043e7e3 <+1411>:	jbe    0x43e8d0 <gaussianiir2d+1648>

239	
240	            /* Filter upwards */
241	            for(; i > 0; i -= width)
   0x000000000043e7e9 <+1417>:	cmp    r12,rbx
   0x000000000043e7ec <+1420>:	jne    0x43e850 <gaussianiir2d+1520>
   0x000000000043e7ee <+1422>:	xchg   ax,ax
   0x000000000043e7f0 <+1424>:	movss  xmm1,DWORD PTR [r14]

232	            ptr[0] *= boundaryscale;
   0x000000000043e7f5 <+1429>:	mulss  xmm1,xmm3
   0x000000000043e7f9 <+1433>:	movss  DWORD PTR [r14],xmm1
   0x000000000043e7fe <+1438>:	mov    rax,r13
   0x000000000043e801 <+1441>:	mov    rdi,rbx
   0x000000000043e804 <+1444>:	data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e810 <+1456>:	movss  xmm1,DWORD PTR [rax+rsi*4]

236	                ptr[i] += nu*ptr[i - width];
   0x000000000043e815 <+1461>:	mulss  xmm1,xmm2
   0x000000000043e819 <+1465>:	add    rax,rdx
   0x000000000043e81c <+1468>:	addss  xmm1,DWORD PTR [rax+rsi*4]
   0x000000000043e821 <+1473>:	movss  DWORD PTR [rax+rsi*4],xmm1

235	            for(i = width; i < numpixels; i += width)
   0x000000000043e826 <+1478>:	add    rdi,rbx
   0x000000000043e829 <+1481>:	jb     0x43e810 <gaussianiir2d+1456>
   0x000000000043e82b <+1483>:	movss  xmm1,DWORD PTR [r14+r11*4]

237	
238	            ptr[i = numpixels - width] *= boundaryscale;
   0x000000000043e831 <+1489>:	mulss  xmm1,xmm3
   0x000000000043e835 <+1493>:	movss  DWORD PTR [r14+r11*4],xmm1

229	        for(step = 0; step < numsteps; step++)
   0x000000000043e83b <+1499>:	inc    ecx
   0x000000000043e83d <+1501>:	cmp    ecx,r15d
   0x000000000043e840 <+1504>:	jne    0x43e7f0 <gaussianiir2d+1424>
   0x000000000043e842 <+1506>:	jmp    0x43e9c0 <gaussianiir2d+1888>
   0x000000000043e847 <+1511>:	nop    WORD PTR [rax+rax*1+0x0]
   0x000000000043e850 <+1520>:	movss  xmm1,DWORD PTR [r14]

232	            ptr[0] *= boundaryscale;
   0x000000000043e855 <+1525>:	mulss  xmm1,xmm3
   0x000000000043e859 <+1529>:	movss  DWORD PTR [r14],xmm1
   0x000000000043e85e <+1534>:	mov    rax,r13
   0x000000000043e861 <+1537>:	mov    rdi,rbx
   0x000000000043e864 <+1540>:	data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e870 <+1552>:	movss  xmm1,DWORD PTR [rax+rsi*4]

236	                ptr[i] += nu*ptr[i - width];
   0x000000000043e875 <+1557>:	mulss  xmm1,xmm2
   0x000000000043e879 <+1561>:	add    rax,rdx
   0x000000000043e87c <+1564>:	addss  xmm1,DWORD PTR [rax+rsi*4]
   0x000000000043e881 <+1569>:	movss  DWORD PTR [rax+rsi*4],xmm1

235	            for(i = width; i < numpixels; i += width)
   0x000000000043e886 <+1574>:	add    rdi,rbx
   0x000000000043e889 <+1577>:	cmp    rdi,r12
   0x000000000043e88c <+1580>:	jb     0x43e870 <gaussianiir2d+1552>
   0x000000000043e88e <+1582>:	movss  xmm1,DWORD PTR [r14+r11*4]

237	
238	            ptr[i = numpixels - width] *= boundaryscale;
   0x000000000043e894 <+1588>:	mulss  xmm1,xmm3
   0x000000000043e898 <+1592>:	movss  DWORD PTR [r14+r11*4],xmm1

242	                ptr[i - width] += nu*ptr[i];
   0x000000000043e89e <+1598>:	mov    rdi,r10
   0x000000000043e8a1 <+1601>:	mov    rax,r9
   0x000000000043e8a4 <+1604>:	data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e8b0 <+1616>:	mulss  xmm1,xmm2
   0x000000000043e8b4 <+1620>:	addss  xmm1,DWORD PTR [rdi]
   0x000000000043e8b8 <+1624>:	movss  DWORD PTR [rdi],xmm1

241	            for(; i > 0; i -= width)
   0x000000000043e8bc <+1628>:	add    rdi,rbp
   0x000000000043e8bf <+1631>:	add    rax,rbx
   0x000000000043e8c2 <+1634>:	jne    0x43e8b0 <gaussianiir2d+1616>

229	        for(step = 0; step < numsteps; step++)
   0x000000000043e8c4 <+1636>:	inc    ecx
   0x000000000043e8c6 <+1638>:	cmp    ecx,r15d
   0x000000000043e8c9 <+1641>:	jne    0x43e850 <gaussianiir2d+1520>
   0x000000000043e8cb <+1643>:	jmp    0x43e9c0 <gaussianiir2d+1888>

239	
240	            /* Filter upwards */
241	            for(; i > 0; i -= width)
   0x000000000043e8d0 <+1648>:	cmp    r12,rbx
   0x000000000043e8d3 <+1651>:	jne    0x43e970 <gaussianiir2d+1808>
   0x000000000043e8d9 <+1657>:	xor    eax,eax
   0x000000000043e8db <+1659>:	test   r8d,r8d
   0x000000000043e8de <+1662>:	je     0x43e903 <gaussianiir2d+1699>
   0x000000000043e8e0 <+1664>:	movss  xmm1,DWORD PTR [r14]

232	            ptr[0] *= boundaryscale;
   0x000000000043e8e5 <+1669>:	mulss  xmm1,xmm3
   0x000000000043e8e9 <+1673>:	movss  DWORD PTR [r14],xmm1
   0x000000000043e8ee <+1678>:	movss  xmm1,DWORD PTR [r14+r11*4]

237	
238	            ptr[i = numpixels - width] *= boundaryscale;
   0x000000000043e8f4 <+1684>:	mulss  xmm1,xmm3
   0x000000000043e8f8 <+1688>:	movss  DWORD PTR [r14+r11*4],xmm1
   0x000000000043e8fe <+1694>:	mov    eax,0x1
   0x000000000043e903 <+1699>:	cmp    r15d,0x1
   0x000000000043e907 <+1703>:	je     0x43e9c0 <gaussianiir2d+1888>

193	    float *ptr;
   0x000000000043e90d <+1709>:	mov    ecx,r15d
   0x000000000043e910 <+1712>:	sub    ecx,eax
   0x000000000043e912 <+1714>:	data16 data16 data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e920 <+1728>:	movss  xmm1,DWORD PTR [r14]

232	            ptr[0] *= boundaryscale;
   0x000000000043e925 <+1733>:	mulss  xmm1,xmm3
   0x000000000043e929 <+1737>:	movss  DWORD PTR [r14],xmm1
   0x000000000043e92e <+1742>:	movss  xmm1,DWORD PTR [r14+r11*4]

237	
238	            ptr[i = numpixels - width] *= boundaryscale;
   0x000000000043e934 <+1748>:	mulss  xmm1,xmm3
   0x000000000043e938 <+1752>:	movss  DWORD PTR [r14+r11*4],xmm1
   0x000000000043e93e <+1758>:	movss  xmm1,DWORD PTR [r14]

232	            ptr[0] *= boundaryscale;
   0x000000000043e943 <+1763>:	mulss  xmm1,xmm3
   0x000000000043e947 <+1767>:	movss  DWORD PTR [r14],xmm1
   0x000000000043e94c <+1772>:	movss  xmm1,DWORD PTR [r14+r11*4]

237	
238	            ptr[i = numpixels - width] *= boundaryscale;
   0x000000000043e952 <+1778>:	mulss  xmm1,xmm3
   0x000000000043e956 <+1782>:	movss  DWORD PTR [r14+r11*4],xmm1

229	        for(step = 0; step < numsteps; step++)
   0x000000000043e95c <+1788>:	add    ecx,0xfffffffe
   0x000000000043e95f <+1791>:	jne    0x43e920 <gaussianiir2d+1728>
   0x000000000043e961 <+1793>:	jmp    0x43e9c0 <gaussianiir2d+1888>
   0x000000000043e963 <+1795>:	data16 data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e970 <+1808>:	movss  xmm1,DWORD PTR [r14]

232	            ptr[0] *= boundaryscale;
   0x000000000043e975 <+1813>:	mulss  xmm1,xmm3
   0x000000000043e979 <+1817>:	movss  DWORD PTR [r14],xmm1
   0x000000000043e97e <+1822>:	movss  xmm1,DWORD PTR [r14+r11*4]

237	
238	            ptr[i = numpixels - width] *= boundaryscale;
   0x000000000043e984 <+1828>:	mulss  xmm1,xmm3
   0x000000000043e988 <+1832>:	movss  DWORD PTR [r14+r11*4],xmm1

242	                ptr[i - width] += nu*ptr[i];
   0x000000000043e98e <+1838>:	mov    rax,r10
   0x000000000043e991 <+1841>:	mov    rdi,r9
   0x000000000043e994 <+1844>:	data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043e9a0 <+1856>:	mulss  xmm1,xmm2
   0x000000000043e9a4 <+1860>:	addss  xmm1,DWORD PTR [rax]
   0x000000000043e9a8 <+1864>:	movss  DWORD PTR [rax],xmm1

241	            for(; i > 0; i -= width)
   0x000000000043e9ac <+1868>:	add    rax,rbp
   0x000000000043e9af <+1871>:	add    rdi,rbx
   0x000000000043e9b2 <+1874>:	jne    0x43e9a0 <gaussianiir2d+1856>

229	        for(step = 0; step < numsteps; step++)
   0x000000000043e9b4 <+1876>:	inc    ecx
   0x000000000043e9b6 <+1878>:	cmp    ecx,r15d
   0x000000000043e9b9 <+1881>:	jne    0x43e970 <gaussianiir2d+1808>
   0x000000000043e9bb <+1883>:	nop    DWORD PTR [rax+rax*1+0x0]

227	    for(x = 0; x < width; x++)
   0x000000000043e9c0 <+1888>:	inc    rsi
   0x000000000043e9c3 <+1891>:	add    r10,0x4
   0x000000000043e9c7 <+1895>:	cmp    rsi,rbx
   0x000000000043e9ca <+1898>:	jne    0x43e7d0 <gaussianiir2d+1392>

243	        }
244	    }
245	
246	    for(i = 0; i < numpixels; i++)
   0x000000000043e9d0 <+1904>:	test   r12,r12
   0x000000000043e9d3 <+1907>:	je     0x43eab5 <gaussianiir2d+2133>

204	    postscale = (float)(pow(dnu/lambda,2*numsteps));
   0x000000000043e9d9 <+1913>:	cvtsd2ss xmm0,xmm0
   0x000000000043e9dd <+1917>:	xor    edx,edx

247	        image[i] *= postscale;
   0x000000000043e9df <+1919>:	cmp    r12,0x7
   0x000000000043e9e3 <+1923>:	jbe    0x43ea8c <gaussianiir2d+2092>
   0x000000000043e9e9 <+1929>:	xor    edx,edx
   0x000000000043e9eb <+1931>:	mov    rcx,r12
   0x000000000043e9ee <+1934>:	and    rcx,0xfffffffffffffff8
   0x000000000043e9f2 <+1938>:	je     0x43ea8c <gaussianiir2d+2092>
   0x000000000043e9f8 <+1944>:	movaps xmm1,xmm0
   0x000000000043e9fb <+1947>:	shufps xmm1,xmm1,0x0
   0x000000000043e9ff <+1951>:	lea    rsi,[r12-0x8]
   0x000000000043ea04 <+1956>:	mov    rdx,rsi
   0x000000000043ea07 <+1959>:	shr    rdx,0x3
   0x000000000043ea0b <+1963>:	xor    eax,eax
   0x000000000043ea0d <+1965>:	bt     rsi,0x3
   0x000000000043ea12 <+1970>:	jb     0x43ea33 <gaussianiir2d+2003>
   0x000000000043ea14 <+1972>:	movups xmm2,XMMWORD PTR [r13+0x0]
   0x000000000043ea19 <+1977>:	movups xmm3,XMMWORD PTR [r13+0x10]
   0x000000000043ea1e <+1982>:	mulps  xmm2,xmm1
   0x000000000043ea21 <+1985>:	mulps  xmm3,xmm1
   0x000000000043ea24 <+1988>:	movups XMMWORD PTR [r13+0x0],xmm2
   0x000000000043ea29 <+1993>:	movups XMMWORD PTR [r13+0x10],xmm3
   0x000000000043ea2e <+1998>:	mov    eax,0x8
   0x000000000043ea33 <+2003>:	test   rdx,rdx
   0x000000000043ea36 <+2006>:	je     0x43ea84 <gaussianiir2d+2084>
   0x000000000043ea38 <+2008>:	mov    rdx,r12
   0x000000000043ea3b <+2011>:	and    rdx,0xfffffffffffffff8
   0x000000000043ea3f <+2015>:	sub    rdx,rax
   0x000000000043ea42 <+2018>:	lea    rsi,[r13+rax*4+0x30]
   0x000000000043ea47 <+2023>:	nop    WORD PTR [rax+rax*1+0x0]
   0x000000000043ea50 <+2032>:	movups xmm2,XMMWORD PTR [rsi-0x30]
   0x000000000043ea54 <+2036>:	movups xmm3,XMMWORD PTR [rsi-0x20]
   0x000000000043ea58 <+2040>:	mulps  xmm2,xmm1
   0x000000000043ea5b <+2043>:	mulps  xmm3,xmm1
   0x000000000043ea5e <+2046>:	movups XMMWORD PTR [rsi-0x30],xmm2
   0x000000000043ea62 <+2050>:	movups XMMWORD PTR [rsi-0x20],xmm3
   0x000000000043ea66 <+2054>:	movups xmm2,XMMWORD PTR [rsi-0x10]
   0x000000000043ea6a <+2058>:	movups xmm3,XMMWORD PTR [rsi]
   0x000000000043ea6d <+2061>:	mulps  xmm2,xmm1
   0x000000000043ea70 <+2064>:	mulps  xmm3,xmm1
   0x000000000043ea73 <+2067>:	movups XMMWORD PTR [rsi-0x10],xmm2
   0x000000000043ea77 <+2071>:	movups XMMWORD PTR [rsi],xmm3
   0x000000000043ea7a <+2074>:	add    rsi,0x40
   0x000000000043ea7e <+2078>:	add    rdx,0xfffffffffffffff0
   0x000000000043ea82 <+2082>:	jne    0x43ea50 <gaussianiir2d+2032>
   0x000000000043ea84 <+2084>:	cmp    r12,rcx
   0x000000000043ea87 <+2087>:	mov    rdx,rcx
   0x000000000043ea8a <+2090>:	je     0x43eab5 <gaussianiir2d+2133>
   0x000000000043ea8c <+2092>:	lea    rax,[r13+rdx*4+0x0]
   0x000000000043ea91 <+2097>:	sub    r12,rdx
   0x000000000043ea94 <+2100>:	data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
   0x000000000043eaa0 <+2112>:	movss  xmm1,DWORD PTR [rax]
   0x000000000043eaa4 <+2116>:	mulss  xmm1,xmm0
   0x000000000043eaa8 <+2120>:	movss  DWORD PTR [rax],xmm1

246	    for(i = 0; i < numpixels; i++)
   0x000000000043eaac <+2124>:	add    rax,0x4
   0x000000000043eab0 <+2128>:	dec    r12
   0x000000000043eab3 <+2131>:	jne    0x43eaa0 <gaussianiir2d+2112>

248	
249	    return;
250	}
   0x000000000043eab5 <+2133>:	add    rsp,0x38
   0x000000000043eab9 <+2137>:	pop    rbx
   0x000000000043eaba <+2138>:	pop    r12
   0x000000000043eabc <+2140>:	pop    r13
   0x000000000043eabe <+2142>:	pop    r14
   0x000000000043eac0 <+2144>:	pop    r15
   0x000000000043eac2 <+2146>:	pop    rbp
   0x000000000043eac3 <+2147>:	ret    
End of assembler dump.

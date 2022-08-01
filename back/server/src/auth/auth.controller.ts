import { Body, Controller, Get, Param, Post, Query, Redirect, Res } from '@nestjs/common';
import { Response } from 'express';
import { ResUserNavi } from 'src/users/dto/res-user-navi.dto';
import { AuthService } from './auth.service';

@Controller('oauth')
export class AuthController {
	constructor(private readonly authService: AuthService) { }

	@Get('login')
	async saveAccessToken(@Res() res: Response, @Query('code') code: string) {
		// console.log("code=", code);
		await this.authService.saveAccessToken(res, code);
	}

	// @Redirect('https://api.intra.42.fr/oauth/authorize?client_id=10fd003cd72e573d39cefc1302e9a5c3a9722ad06f7bffe91bf3b3587ace5036&redirect_uri=http%3A%2F%2F10.19.226.233%3A3000%2Foauth%2Flogin&response_type=code', 301)
	@Redirect('https://api.intra.42.fr/oauth/authorize?client_id=afc0a3e907f953c39d371c4fee3fd72b29b320fbf95da01448b787745a0e066c&redirect_uri=http%3A%2F%2F10.19.226.233%3A3000%2Foauth%2Flogin&response_type=code', 301)
	@Get('42')
	getOauthPage() {
		// console.log("authorization/42");
		return {
		};
	}

	@Post('sendEmail')
	async sendEmail(
		@Query('id') id: string,
		@Body('email') email: string,
	): Promise<void> {
		await this.authService.sendEmail(id, email);
	}

	@Post('validEmail')
	async validEmail(
		@Query('id') id: string,
		@Body('code') code: string,
	): Promise<ResUserNavi> {
		return await this.authService.validEmail(id, code);
	}
}

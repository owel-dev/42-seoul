import { IsEmail, Length } from 'class-validator'

export class CreateUserDto {
	@Length(1, 10)
	intraId: string;
	
	@Length(1, 10)
	nickName: string;

	@IsEmail()
	intraEmail: string;
	
	avatar: string;
	status: string;
	role: string;
	channelId: string;
}

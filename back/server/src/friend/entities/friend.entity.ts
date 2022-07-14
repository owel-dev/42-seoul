import { User } from "src/users/entities/user.entity";
import { Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";

@Entity('friend')
export class Friend {
	@PrimaryGeneratedColumn()
	frined_id: number;

	@Column('varchar')
	status: string;

	// 요청 보낸사람
	@ManyToOne(() => User)
	friend_1: User;

	// 요청 받은사람
	@ManyToOne(() => User)
	friend_2: User;
}

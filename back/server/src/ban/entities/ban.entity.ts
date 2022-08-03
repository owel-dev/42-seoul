import { User } from 'src/users/entities/user.entity';
import { Entity, ManyToOne, PrimaryGeneratedColumn } from 'typeorm';

@Entity('ban')
export class Ban {
  @PrimaryGeneratedColumn()
  ban_id: number;

  // 요청 보낸사람
  @ManyToOne(() => User)
  ban_1: User;

  // 요청 받은사람
  @ManyToOne(() => User)
  ban_2: User;
}
